#include <sweet/unit/Config.h>
#include <sweet/unit/TestRunner.h>
#include <sweet/unit/TestResults.h>
#include <sweet/unit/TestReporter.h>
#include <sweet/unit/TestReporterStdout.h>
#include <sweet/unit/TimeHelpers.h>
#include <sweet/unit/MemoryOutStream.h>
#include <cstring>


namespace UnitTest {

int RunAllTests()
{
	TestReporterStdout reporter;
	TestRunner runner(reporter);
	return runner.RunTestsIf(Test::GetTestList(), NULL, True(), 0);
}


TestRunner::TestRunner(TestReporter& reporter)
	: m_reporter(&reporter)
	, m_result(new TestResults(&reporter))
	, m_timer(new Timer)
{
	m_timer->Start();
}

TestRunner::~TestRunner()
{
	delete m_result;
	delete m_timer;
}

int TestRunner::Finish() const
{
    float const secondsElapsed = m_timer->GetTimeInMs() / 1000.0f;
    m_reporter->ReportSummary(m_result->GetTotalTestCount(), 
							  m_result->GetFailedTestCount(), 
							  m_result->GetFailureCount(), 
							  secondsElapsed);
    
	return m_result->GetFailureCount();
}

bool TestRunner::IsTestInSuite(const Test* const curTest, char const* suiteName) const
{
	using namespace std;
	return (suiteName == NULL) || !strcmp(curTest->m_details.suiteName, suiteName);
}

void TestRunner::RunTest(TestResults* const result, Test* const curTest, int const maxTestTimeInMs) const
{
	CurrentTest::Results() = result;

	Timer testTimer;
	testTimer.Start();

	result->OnTestStart(curTest->m_details);

	curTest->Run();

	int const testTimeInMs = testTimer.GetTimeInMs();
	if (maxTestTimeInMs > 0 && testTimeInMs > maxTestTimeInMs && !curTest->m_timeConstraintExempt)
	{
	    MemoryOutStream stream;
	    stream << "Global time constraint failed. Expected under " << maxTestTimeInMs <<
	            "ms but took " << testTimeInMs << "ms.";

	    result->OnTestFailure(curTest->m_details, stream.GetText());
	}

	result->OnTestFinish(curTest->m_details, testTimeInMs/1000.0f);
}

}
