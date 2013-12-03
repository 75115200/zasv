package whu.zhengdianclub.group1;

import android.content.Context;
import android.content.Intent;
import android.content.BroadcastReceiver;

/**
 * Glue class: connects AlarmAlert IntentReceiver to AlarmAlert
 * activity.  Passes through Alarm ID.
 */
public class AlarmReceiver extends BroadcastReceiver {

    /** If the alarm is older than STALE_WINDOW seconds, ignore.  It
        is probably the result of a time or timezone change */
    private final static int STALE_WINDOW = 60 * 30;

    @Override
    public void onReceive(Context context, Intent intent) {
        long now = System.currentTimeMillis();
        int id = intent.getIntExtra(Alarms.ID, 0);
        long setFor = intent.getLongExtra(Alarms.TIME, 0);

        /* FIXME Intentionally verbose: always log this until we've
           fully debugged the app failing to start up */
        Log.v("AlarmReceiver.onReceive() id " + id + " setFor " + setFor +
              " now " + now);

        if (now > setFor + STALE_WINDOW * 1000) {
            if (Log.LOGV) Log.v("AlarmReceiver ignoring stale alarm intent id"
                                + id + " setFor " + setFor + " now " + now);
            return;
        }

        /* Wake the device and stay awake until the AlarmAlert intent is
         * handled. */
        AlarmAlertWakeLock.acquire(context);

        /* Close dialogs and window shade */
        Intent i = new Intent(Intent.ACTION_CLOSE_SYSTEM_DIALOGS);
        context.sendBroadcast(i);

        /* launch UI, explicitly stating that this is not due to user action
         * so that the current app's notification management is not disturbed */
        Intent fireAlarm = new Intent(context, AlarmAlert.class);
        fireAlarm.putExtra(Alarms.ID, id);
        fireAlarm.putExtra(Alarms.LABEL, intent.getStringExtra(Alarms.LABEL));
        fireAlarm.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK | Intent.FLAG_ACTIVITY_NO_USER_ACTION);
        context.startActivity(fireAlarm);
   }
}
