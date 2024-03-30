from saleae import automation
import os.path
import csv

def i2c_capture():
    with automation.Manager.connect(port=10430) as manager:
        device_configuration = automation.LogicDeviceConfiguration(
            enabled_digital_channels=[0, 1],
            digital_sample_rate=16000000,
        )

        capture_configuration = automation.CaptureConfiguration(
            capture_mode=automation.TimedCaptureMode(duration_seconds=3)
        )

        with manager.start_capture(
                device_id='F710115DE721C4DD',
                device_configuration=device_configuration,
                capture_configuration=capture_configuration) as capture:

            capture.wait()
            i2c_anayliser = capture.add_analyzer('I2C', settings={
                'SDA':0,
                'SCL':1
                }, )
            

            analyzer_export_filepath = '/tmp/i2c_data.csv'
            capture.legacy_export_analyzer(
                filepath=analyzer_export_filepath,
                analyzer=i2c_anayliser,
                radix=automation.saleae.automation.RadixType.HEXADECIMAL
            )

# i2c_capture()

def get_data():
    with open('/tmp/i2c_data.csv') as f:
        reader = csv.DictReader(f);
        data = [int(i['Data'], 16) for i in reader]
        return data


print(get_data())
