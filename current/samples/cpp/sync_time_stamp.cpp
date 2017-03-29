/*!
  \~japanese
  \example sync_time_stamp.cpp �Z���T�� PC �̃^�C���X�^���v�𓯊�����
  \~english
  \example sync_time_stamp.cpp Timestamp synchronization between PC and sensor
  \~
  \author Satofumi KAMIMURA

  $Id$
*/

#include "Urg_driver.h"
#include "Connection_information.h"
#include "ticks.h"
#include <iostream>

using namespace qrk;
using namespace std;


namespace
{
    void print_timestamp(Urg_driver& urg)
    {
        enum { Print_times = 3 };

        urg.start_measurement(Urg_driver::Distance, Print_times);
        for (int i = 0; i < Print_times; ++i) {
            long time_stamp;
            vector<long> data;
            urg.get_distance(data, &time_stamp);

            cout << ticks() << ", " << time_stamp << endl;
        }
    }
}


int main(int argc, char *argv[])
{
    Connection_information information(argc, argv);

    // \~japanese �ڑ�
    // \~english Connects to the sensor
    Urg_driver urg;
    if (!urg.open(information.device_or_ip_name(),
                  information.baudrate_or_port_number(),
                  information.connection_type())) {
        cout << "Urg_driver::open(): "
             << information.device_or_ip_name() << ": " << urg.what() << endl;
        return 1;
    }

    // \~japanese �f�[�^�͂P�X�e�b�v�̂ݎ擾����
    // \~english Will obtain only one step of measurement data
    int min_step = urg.min_step();
    urg.set_scanning_parameter(min_step, min_step);

    //
    // \~japanese ��r�p�� PC �ƃZ���T�̃^�C���X�^���v��\������
    // \~english Just to compare, shows the current PC timestamp and sensor timestamp
    print_timestamp(urg);
    cout << endl;

    // \~japanese �Z���T�� PC �̃^�C���X�^���v��ݒ肵�A
    // \~japanese �����f�[�^���擾�����Ƃ��ɓ�����^�C���X�^���v���A
    // \~japanese PC ���瓾����^�C���X�^���v�Ɠ����ɂȂ�悤�ɂ���
    // \~english Configures the PC timestamp into the sensor
    // \~english The timestamp value which comes in the measurement data
    // \~english will match the timestamp value from the PC
    urg.set_sensor_time_stamp(ticks());

    // \~japanese �ݒ��� PC �ƃZ���T�̃^�C���X�^���v��\������
    // \~english Displays the PC timestamp and sensor timestamp after configuration
    print_timestamp(urg);

    return 0;
}
