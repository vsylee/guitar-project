package com.example.veronicalee.laserukelele;

import android.content.Context;
import android.hardware.usb.UsbAccessory;
import android.hardware.usb.UsbManager;
import android.os.ParcelFileDescriptor;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;

public class MainActivity extends AppCompatActivity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /*mUSBManager = UsbManager.getInstance(this);
        UsbAccessory acc = mUSBManager.getAccessoryList()[0];
        if (!mUSBManager.hasPermission(acc)) return;*/

        UsbManager mUSBManager = (UsbManager) getSystemService(Context.USB_SERVICE);
        UsbAccessory acc = (UsbAccessory)
                intent.getParcelableExtra(UsbManager.EXTRA_ACCESSORY);

        ParcelFileDescriptor mFD = mUSBManager.openAccessory(acc);
        if (mFD != null) {
            FileDescriptor fd = mFD.getFileDescriptor();
            FileInputStream mIS = new FileInputStream(fd); // receive messages
            FileOutputStream mOS = new FileOutputStream(fd); // send messages
        }
    }
}
