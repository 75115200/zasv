package whu.zhengdianclub.group1;

import android.content.Context;
import android.net.Uri;
import android.preference.RingtonePreference;
import android.util.AttributeSet;

public class AlarmPreference extends RingtonePreference {
    public Uri mAlert;
    private IRingtoneChangedListener mRingtoneChangedListener;

    public interface IRingtoneChangedListener {
        public void onRingtoneChanged(Uri ringtoneUri);
    };

    public AlarmPreference(Context context, AttributeSet attrs) {
        super(context, attrs);
    }

    public void setRingtoneChangedListener(IRingtoneChangedListener listener) {
        mRingtoneChangedListener = listener;
    }

    @Override
    protected void onSaveRingtone(Uri ringtoneUri) {
        if (ringtoneUri != null) {
            mAlert = ringtoneUri;
            if (mRingtoneChangedListener != null) {
                mRingtoneChangedListener.onRingtoneChanged(ringtoneUri);
            }
        }
    }

    @Override
    protected Uri onRestoreRingtone() {
        return mAlert;
    }
}
