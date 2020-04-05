#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// File declarations for future function uses
#define YearsOldToDrive       16
int YearsLeft;// Calculation if user is below age 16

// Lets just pretend this is a actual API that stores
// data of criminals
const char * const criminalNames[] = {
    "Bob",
    "Jeff",
    "Yor",
    "John"
};
// Each index goes with each index of criminalName, so index 0 goes with
// "Bob" etc..
const char * const criminalIdeas[] = {
    "Rape",
    "Murder",
    "GTA",
    "Gang Violence"
};

const char *StolenCarLicense = "44-detfg";

typedef struct {
    char *Name;
    int Age;
    bool canDrive;
} setupUserInfo;

/* USED IF USER IS 16 OR OLDER */
typedef struct {
    char *LicenceId;
    char *LicenceValidData;
    char *VehicleLicence;
    char *NameOnLicense;
    char *CriminalRecord;
} CheckDriver;

typedef struct {
    char *CriminalNameFound;
    char *Details;
} CaughtCriminal;

static void
GetInformation(setupUserInfo *UserInfo,char *Name, int Age, bool canDrive_) {
    
    // Setting up user info, will do more with it later on
    UserInfo->Name=Name;
    UserInfo->Age=Age;
    UserInfo->canDrive=canDrive_;
}

// returns 16, then the ammount of years left before user
// can legally drive
static int YearsLeft_(setupUserInfo *UserInfo) {
    if(UserInfo->Age < YearsOldToDrive) {
        YearsLeft = YearsOldToDrive-UserInfo->Age;
    } else {
        YearsLeft=0; // Meaning the user is old enough
    }
    return YearsLeft;
}

static void
checkLicence(
    setupUserInfo * UserInfo,
    CaughtCriminal * CghtCrmnl,
    CheckDriver *ChkDr,
    char LicenceId[50], 
    char LicenceValidDate[20], 
    char VehicleLicence[50],
    char NameOnLicence[100]
) {
    ChkDr->LicenceId=LicenceId;
    ChkDr->LicenceValidData=LicenceValidDate;
    ChkDr->VehicleLicence=VehicleLicence;
    ChkDr->NameOnLicense=NameOnLicence;
    
    char CriminalDetails[100];
    
    for(int i = 0; i < sizeof(criminalNames)/sizeof(criminalNames[0]); i++) {
        if((strcmp(UserInfo->Name,criminalNames[i])==0)) {
            CghtCrmnl->CriminalNameFound=UserInfo->Name;
            sprintf(CriminalDetails,"%s stole car with licence %s. \nName on licence: %s",UserInfo->Name,ChkDr->VehicleLicence,ChkDr->NameOnLicense);
            CghtCrmnl->Details=CriminalDetails;
            
            FILE *WriteFoundInformation;
            
            WriteFoundInformation = fopen("CriminalCaught.ccdt","w");
            fputs(CghtCrmnl->Details,WriteFoundInformation);
            fputs("\n",WriteFoundInformation);
            fputs("CAUGHT,CASE CLOSED",WriteFoundInformation);
            
            fclose(WriteFoundInformation);
            
            WriteFoundInformation = fopen("CriminalCaught.ccdt","r");
            if(WriteFoundInformation==NULL){
                fprintf(stderr,"\033[0;31mSomething went wrong when storing information about the criminal");
                exit(EXIT_FAILURE);
            } else {
                fprintf(stdout,"\033[0;32mWork is all done");
                exit(EXIT_SUCCESS);
            }
            break;
        }
    }
}

int main(void) {
    setupUserInfo * UserInfo = (setupUserInfo *) malloc(sizeof(setupUserInfo));
    CheckDriver * ChkDr = (CheckDriver *) malloc(sizeof(CheckDriver));
    CaughtCriminal *CghtCrmnl = (CaughtCriminal *) malloc(sizeof(CaughtCriminal));
    
    GetInformation(UserInfo,"John",15,false);
    YearsLeft_(UserInfo);
    checkLicence(UserInfo,CghtCrmnl,ChkDr,"12edbyJju","1/15/2021","44-detfg","Johny");
}
