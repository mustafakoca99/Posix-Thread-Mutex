#include <pthread.h>
#include <iostream>
#include <Windows.h>
#include <conio.h>

using namespace std;

static double vadesizHesap = 1000.00f;
pthread_mutex_t mustafa = PTHREAD_MUTEX_INITIALIZER;

void* ParaYatir(void* miktar)
{
    pthread_mutex_lock(&mustafa);
    double para = vadesizHesap;
    Sleep(2000);
    para += *(double *)miktar;
    vadesizHesap = para;
    pthread_mutex_unlock(&mustafa);
    return NULL;
}

void* ParaCek(void* miktar)
{
    pthread_mutex_lock(&mustafa);
    double para = vadesizHesap;
    Sleep(2000);
    para -= *(double *)miktar;
    vadesizHesap = para;
    pthread_mutex_unlock(&mustafa);
    return NULL;
}

int main(int argc, char* argv[])
{
    pthread_t thread1, thread2;
    double cekilecekMiktar = 0, yatirilacakMiktar = 0;
    cout << endl << "Hesabinizdaki para tutari:" << vadesizHesap << endl;
    cout << endl << "Cekilecek para tutarini giriniz:";
    cin >> cekilecekMiktar;
    cout << endl << "Yatirilacak para tutarini giriniz:";
    cin >> yatirilacakMiktar;
    int sonuc = pthread_create(&thread1, NULL, ParaYatir, (void*)&yatirilacakMiktar);
    if (sonuc) _exit(-1);
    sonuc = pthread_create(&thread2, NULL, ParaCek, (void*)&cekilecekMiktar);
    if (sonuc) _exit(-1);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    cout << endl << "Hesabinizda bulunan para:" << vadesizHesap;
    cin >> sonuc;
    return 0;
}
