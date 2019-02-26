#ifndef WIFI_H
#define	WIFI_H

#define CITYID_LEN		40
#define APITOKEN_LEN	40

extern char cityid[CITYID_LEN];
extern char apitoken[APITOKEN_LEN];

void setupWiFi(void);
void resetWiFi(void);

#endif /* WIFI_H */
