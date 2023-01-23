
#include <obs.h>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-properties.h>

#include <Notify.h>
#include "plugin-macros.generated.h"
#include <Windows.h>
#include <string>
#include <format>

using namespace std;
OBS_DECLARE_MODULE()
//OBS_MODULE_USE_DEFAULT_LOCALE(PLUGIN_NAME, "en-US")

extern struct obs_source_info notificationSourceStruct;

void cPlaySound()
{
	//PlaySound(TEXT("D:/Coding/OBS Plugin/Testing2/NotifySound.wav"), NULL, SND_ASYNC);
}

void StartNotification() {



	char *RecordOutputPath = obs_frontend_get_current_record_output_path();
	string path =  "../../obs-plugins/64bit/obs-notify/";
	string Args = format("obs-notify.exe {} {} {} {} {} {} {}", NotifySettings.AnimationHoldTime,
			     NotifySettings.AnimationFadeTime,
			     NotifySettings.ShowNotification,
			     NotifySettings.ShowPath,
				 NotifySettings.isSound,
			     NotifySettings.NotificationVolume,
			     RecordOutputPath
	);
	string command = format("start {}{}", path, Args);
	//string command = format("start ../../obs-plugins/64bit/TestNotify/obs-notify-animationVS.exe 2500.00 400.00 true false false 5", path, Args);
	blog(LOG_INFO, "%s", command.data());
	system(command.data());
	//system("DIR");
}

void event_callback(enum obs_frontend_event event, void *private_data)
{
	if (event == OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTED) {
		blog(LOG_INFO,"HIDE1 OBS_FRONTEND_EVENT_REPLAY_BUFFER_STARTED 22");

	} else if (event == OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPED) {
		blog(LOG_INFO, "HIDE1 OBS_FRONTEND_EVENT_REPLAY_BUFFER_STOPPED");
	} else if (event == OBS_FRONTEND_EVENT_REPLAY_BUFFER_SAVED) {
		blog(LOG_INFO, "HIDE1 OBS_FRONTEND_EVENT_REPLAY_BUFFER_SAVED");	
		obs_source_t *source = obs_get_source_by_name(notificationSourceStruct.get_name(private_data));
		bool isHidden = obs_source_active(source);

		if (isHidden)
			StartNotification();

	}
}


bool obs_module_load(void)
{
	blog(LOG_INFO, "HIDE1 plugin loaded successfully (version %s)",
	     PLUGIN_VERSION);


	obs_register_source(&notificationSourceStruct);
	obs_frontend_add_event_callback(event_callback, 0);

	return true;
}

void obs_module_unload()
{
	blog(LOG_INFO, "HIDE1 plugin unloaded");
}
