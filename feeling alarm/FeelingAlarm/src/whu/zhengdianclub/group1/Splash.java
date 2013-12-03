package whu.zhengdianclub.group1;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.view.WindowManager;

public class Splash extends Activity {
    /** Called when the activity is first created. */
	
	@Override
    public void onCreate(Bundle savedInstanceState)
	{
	      super.onCreate(savedInstanceState);
	      //»•µÙ±ÍÃ‚¿∏
	      getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
	    		  							WindowManager.LayoutParams.FLAG_FULLSCREEN);
	      setContentView(R.layout.splash);
	      
	      Handler pause = new Handler();  
	     // pause.postDelayed(new SplashHandler(), 1000);
	      pause.postDelayed(new SplashHandler(),1000);
   	}
	
	class SplashHandler implements Runnable
	{  	  
	    public void run() 
	    {  
	        startActivity(new Intent(getApplication(),AlarmClock.class));  
	        Splash.this.finish();  
	    }  
	}
	
    protected void onPause()
    {
    	super.onPause();
    }
    
    protected void onResume()
    {
    	super.onResume();
    }
}


