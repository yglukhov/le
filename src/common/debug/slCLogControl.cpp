#include "slCLogControl.h"
#include <common/types/slCNumber.h>

LE_NAMESPACE_START

CLogControl::CLogControl(const CString& threadName)
{
	static CNumber threadID;
	++threadID;
	CString logFileName = threadID.valueAsString() + " - " + threadName + ".runlog";
	mLogFile.open(logFileName, eOpenWrite | eOpenTruncate);
}

void CLogControl::attachToFile(const CString& name, UInt32 minPriority)
{

}

void CLogControl::attachToScreen(UInt32 minPriority)
{

}

LE_NAMESPACE_END
