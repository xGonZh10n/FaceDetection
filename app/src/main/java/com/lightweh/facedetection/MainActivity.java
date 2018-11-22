package com.lightweh.facedetection;

import android.Manifest;
import android.content.pm.PackageManager;
import android.os.Build;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    private static final int REQUEST_PERMISSION = 1;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        if (hasPermission()) {
            if (null == savedInstanceState) {
                setFragment();
            }
        } else {
            requestPermission();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {

        if (requestCode == REQUEST_PERMISSION) {
            if (grantResults.length == 1 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                setFragment();
            } else {
                requestPermission();
            }
        } else {
            super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    private boolean hasPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            return checkSelfPermission(Manifest.permission.CAMERA) == PackageManager.PERMISSION_GRANTED;
        } else {
            return true;
        }
    }

    private void requestPermission() {
        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.M) {
            if (shouldShowRequestPermissionRationale(Manifest.permission.CAMERA)) {
                Toast.makeText(MainActivity.this, "Camera permission are required for this demo", Toast.LENGTH_LONG).show();
            }
            requestPermissions(new String[]{Manifest.permission.CAMERA}, REQUEST_PERMISSION);
        }
    }

    private void setFragment() {
        getSupportFragmentManager()
                .beginTransaction()
                .replace(R.id.container, CameraFragment.newInstance())
                .commitNowAllowingStateLoss();
    }
}
