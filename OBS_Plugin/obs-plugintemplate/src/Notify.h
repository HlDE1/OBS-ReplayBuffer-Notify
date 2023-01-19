#include <obs.h>

struct NotifySettingsStruct {
	float AnimationHoldTime;
	float AnimationFadeTime;
	bool ShowNotification;
	bool ShowPath;
	bool isSound;
	float NotificationVolume;
};

extern NotifySettingsStruct NotifySettings;

class Notify {
public:
	Notify(obs_data_t *settings, obs_source_t *source);
	~Notify();
	//void NotifyUpdate(obs_data_t *settings);

private:
	//NotifySettingsStruct NotifySettings;
};

