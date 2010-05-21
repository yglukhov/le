#include <al/include/al.h>
#include <al/include/alc.h>

#include "slCSoundContext.h"
#include "slCSource.h"
#include "base/slCSourceImpl.hp"

namespace sokira
{
	namespace le
	{

CSoundContext::CSoundContext()
{
//	alutInit();
ALfloat listenerPos[]={0.0,0.0,4.0};
ALfloat listenerVel[]={0.0,0.0,0.0};
ALfloat	listenerOri[]={0.0,0.0,1.0, 0.0,1.0,0.0};
//	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
//	std::cout << "alListener3f ALERROR: " << alGetError() << std::endl;
	ALCdevice * device = alcOpenDevice(NULL);
	if (!device)
	{
		std::cout << "Could not open device" << std::endl;
	}

	ALCcontext * context = alcCreateContext(device, NULL);
	if (!context)
	{
		std::cout << "Could not create context" << std::endl;
	}

	alcMakeContextCurrent(context);

    alGetError(); // clear any error messages
    alListenerfv(AL_POSITION,listenerPos);
    alListenerfv(AL_VELOCITY,listenerVel);
    alListenerfv(AL_ORIENTATION,listenerOri);

    if(alGetError() != AL_NO_ERROR)
    {
		std::cout << "Could not create context" << std::endl;
//        printf("- Error creating buffers !!\n");
		LE_ASSERT(false);
      //  exit(1);
    }
}

CSource CSoundContext::createSource()
{
	return CSource(new CSourceImpl());
}

	} // namespace le
} // namespace sokira
