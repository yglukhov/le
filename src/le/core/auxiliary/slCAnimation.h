#if !defined SL_LE_core_auxiliary_slCAnimation_h
#define SL_LE_core_auxiliary_slCAnimation_h

#include <le/core/slCObject.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/geometry/slTCPoint2D.h>

namespace sokira
{
	namespace le
	{

class CAnimator : CObject
{
	public:
		virtual void animate(Float32 progress)
		{

		}
};

template <typename T>
class TCValueAnimator : public CAnimator
{
	typedef TCFunction<TSTypeList<T> > TSetter;

	public:
		TCValueAnimator(T startValue, T endValue, TSetter setter) :
			mStartValue(startValue),
			mEndValue(endValue),
			mSetter(setter)
		{

		}

		virtual void animate(Float32 progress)
		{
			mSetter(mStartValue + (mEndValue - mStartValue) * progress);
		}

	private:
		T mStartValue;
		T mEndValue;
		TSetter mSetter;
};

template <typename T>
class TCValueAnimator<TCPoint2D<T> >
{
	typedef TCPoint2D<T> TType;
	typedef TCFunction<TSTypeList<TType> > TSetter;

	public:
		TCValueAnimator(TType startValue, TType endValue, TSetter setter) :
			mStartValue(startValue),
			mEndValue(endValue),
			mSetter(setter)
		{

		}

		virtual void animate(Float32 progress)
		{
			mSetter(TType(mStartValue.x() + (mEndValue.x() - mStartValue.x()) * progress,
						mStartValue.y() + (mEndValue.y() - mStartValue.y()) * progress));
		}

	private:
		TType mStartValue;
		TType mEndValue;
		TSetter mSetter;
};

class CAnimationCurve : CObject
{
	virtual Float32 deformProgress(Float32 progress) const
	{
		return progress;
	}
};

class CAnimation : CObject
{
	public:
		void addAnimator(CAnimator* animator);
		void setLoopsCount(SInt32 loopsCount);
		void setLoopDuration(UInt32 milliSeconds);

		// Progress of current loop
		Float32 progress() const;
		void setProgress(Float32 progress);

		Bool isReversed() const;
		void setReversed(Bool reversed);

		Bool setAnimationCurve(CAnimationCurve* curve);

		void start();
		void stop();

		void run(); // run animation synchronously. If loops count is infinite,
					// only one loop will perform

		void addNextAnimation(CAnimation* animation);

};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_auxiliary_slCAnimation_h
