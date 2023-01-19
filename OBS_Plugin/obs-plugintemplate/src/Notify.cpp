#include <obs.h>
#include <obs-module.h>
#include <obs-frontend-api.h>
#include <obs-properties.h>
#include "Notify.h"

using namespace std;
NotifySettingsStruct NotifySettings = {};

static void notification_get_defaults(obs_data_t *settings)
{
	obs_data_set_default_bool(settings, "ShowNotification_Bool", true);
	obs_data_set_default_bool(settings, "isSound_Bool", true);
	obs_data_set_default_bool(settings, "ShowPath_Bool", true);
	obs_data_set_default_double(settings, "animationHoldTime_Float", 2500);
	obs_data_set_default_double(settings, "animationFadeTime_Float", 400);
	obs_data_set_default_double(settings, "Volume_Float", 50);
}

void NotifyUpdate_Var(obs_data_t *settings)
{

	NotifySettings = {
		.AnimationHoldTime = (float)obs_data_get_double(
			settings, "animationHoldTime_Float"),
		.AnimationFadeTime = (float)obs_data_get_double(
			settings, "animationFadeTime_Float"),

		.ShowNotification =
			obs_data_get_bool(settings, "ShowNotification_Bool"),
		.ShowPath = obs_data_get_bool(settings, "ShowPath_Bool"),
		.isSound = obs_data_get_bool(settings, "isSound_Bool"),
		.NotificationVolume =
			(float)obs_data_get_double(settings, "Volume_Float"),
	};
}

Notify::Notify(obs_data_t *settings, obs_source_t *source)
{
	NotifyUpdate_Var(settings);
}
Notify::~Notify() {}

static void Notify_destroy(void *data)
{
	auto *ctx = static_cast<Notify *>(data);
	delete ctx;
}
static void *notify_capture_create(obs_data_t *settings, obs_source_t *source)
{
	return new Notify(settings, source);
}

static const char *notify_get_name(void *type_data)
{
	UNUSED_PARAMETER(type_data);
	//const char *Title = obs_module_text("TitleName");
	//blog(LOG_INFO, "TitleName: %s", Title);
	return "Replay Buffer Notification";
}

static obs_properties_t *notify_get_properties(void *data)
{
	char *RecordOutputPath = obs_frontend_get_current_record_output_path();
	blog(LOG_INFO, "HIDE1 filter_get_properties %s", RecordOutputPath);

	obs_properties_t *props = obs_properties_create();
	obs_properties_add_float(props, "animationHoldTime_Float",
				 "Animation-Hold Time (ms)", 0, 10000, 500);
	obs_properties_add_float(props, "animationFadeTime_Float",
				 "Animation-Fade Time (ms)", 0, 2000, 50);
	obs_properties_add_float(props, "Volume_Float",
				 "Notification Ping Volume", 0, 100, 1);

	obs_properties_add_bool(props, "ShowNotification_Bool",
				"Show Notification");
	obs_properties_add_bool(props, "isSound_Bool", "Sound");
	obs_properties_add_bool(props, "ShowPath_Bool", "Show Recording Path");

	return props;
}
static void Notify_Update(void *data, obs_data_t *settings)
{
	//obs_data_set_default_double(settings, "Volume_Float", 50);

	NotifyUpdate_Var(settings);
	//blog(LOG_INFO, "%f", NotifySettings.NotificationVolume);
}

struct obs_source_info notificationSourceStruct = {
	.id = "replaybuffer_notification",
	.type = OBS_SOURCE_TYPE_INPUT,
	//.output_flags = OBS_SOURCE_AUDIO,
	.get_name = notify_get_name,
	.create = notify_capture_create,
	.destroy = Notify_destroy,
	.get_defaults = notification_get_defaults,
	.get_properties = notify_get_properties,
	.update = Notify_Update,
	.icon_type = OBS_ICON_TYPE_WINDOW_CAPTURE,
};
