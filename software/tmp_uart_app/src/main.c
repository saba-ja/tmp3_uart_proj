#include "xparameters.h"
#include "sleep.h"
#include "stdio.h"
#include "PmodTMP3.h"

void DemoInit();
void DemoRun();
void DemoCleanup();

PmodTMP3 myDevice;

int main() {
	DemoInit();
	DemoRun();
	DemoCleanup();
	return 0;
}

void DemoInit() {
	printf("Initializing PmodTMP3 device");
	TMP3_begin(&myDevice, XPAR_PMODTMP3_0_AXI_LITE_IIC_BASEADDR, TMP3_ADDR);
}

void DemoRun() {
	double temp = 0.0;
	double temp2 = 0.0;
	double temp3 = 0.0;

	while (1) {
		temp = TMP3_getTemp(&myDevice);
		temp2 = TMP3_CtoF(temp);
		temp3 = TMP3_FtoC(temp2);

		int temp2_round = 0;
		int temp2_int = 0;
		int temp2_frac = 0;
		// Round to nearest hundredth multiply by 100
		if (temp2 < 0) {
			temp2_round = (int) (temp2 * 1000 - 5 ) / 10;
			temp2_frac = -temp2_round  % 100;
		} else {
			temp2_round = (int) (temp2 * 1000 + 5 ) /10;
			temp2_frac = temp2_round  % 100;
		}

		temp2_int = temp2_round /100;

		int temp3_round = 0;
		int temp3_int = 0;
		int temp3_frac = 0;
		// Round to nearest hundredth multiply by 100
		if (temp3 < 0) {
			temp3_round = (int) (temp3 * 1000 - 5 ) /10;
			temp3_frac = -temp3_round  % 100;
		} else {
			temp3_round = (int) (temp3 * 1000 + 5 ) /10;
			temp3_frac = temp3_round  % 100;
		}

		temp3_int = temp3_round /100;

		printf("Temperature: %d.%d in F\n\r", temp2_int, temp2_frac);
		printf("Temperature: %d.%d in C\n\r", temp3_int, temp3_frac);
		sleep(1);
	}

}

void DemoCleanup() {
	TMP3_end(&myDevice);
	printf("CLosing connection to PmodTMP3 device");
}
