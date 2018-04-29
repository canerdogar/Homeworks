#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <vector>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

enum DIRECTION {WEST, SOUTH, EAST, NORTH};//Directions of the crossroad

#include "writeOutput.h"//Outputs of the simulation

int arabasayisi=0;
pthread_mutex_t arabasayisimutexi;


class CrossRoad//Class for the crossroad
{
	private:
		int N;// It is the number of intersections.
		int *lightState;// Its value is the direction of the green light on the intersection, -1 in the night mode. Its size is N.
		pthread_mutex_t *mutexforcv;
		int *numCarfromWest,*numCarfromEast,*numCarfromSouth,*numCarfromNorth;
		int *numCarFromWestToNorth,*numCarFromWestToSouth,*numCarFromWestToEast;
		int *numCarFromEastToSouth,*numCarFromEastToWest,*numCarFromEastToNorth;
		int *numCarFromSouthToEast,*numCarFromSouthToNorth,*numCarFromSouthToWest;
		int *numCarFromNorthToEast,*numCarFromNorthToSouth,*numCarFromNorthToWest;
		pthread_cond_t *westgec,*eastgec,*southgec,*northgec;
		pthread_cond_t *westtonorth,*westtoeast,*westtosouth,*easttosouth,*easttowest,*easttonorth,*southtoeast,*southtonorth,*southtowest,*northtoeast,*northtosouth,*northtowest;
		vector<string> *bekleyenler;
	public:
		CrossRoad(int _N,int _mode);//Constructor
		void Enter(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To);//Vehicles call this function for entering the intersection
		void Exit(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To);//Vehicles call this function for exiting the intersection
		void SetGreenLight(int intersectionCode);//Call this function for turning green traffic lights on in the given intersection
};

typedef struct//Struct for the intersections in the day mode
{
	int intersectionCode;//Id of the intersection
	int duration;//Duration of the green light in the day mode
	CrossRoad *crossroad;//CrossRoad class object of the intersection
} intersectionData;

typedef struct{
	int intersectionCode;
	DIRECTION From;
	DIRECTION To;
} pathData;

typedef struct{
	int arriveTime;
	int moveTime;
	int vehicleCode;
	CrossRoad *crossroad;
	vector<pathData>paths;
} carData;

void *trafficLight(void *data)//Traffic light thread
{
	//cout<<"olusturdu mu"<<endl;
	intersectionData *iData=(intersectionData *)data;//Getting intersection data
	while(true)
	{
		usleep(iData->duration*1000);//Waiting until the green light on the next direction turns on
		//cout<<"cagiracak"<<endl;
		(iData->crossroad)->SetGreenLight(iData->intersectionCode);//Turning next green light on the next direction on
	}

}

void *car(void *data){
	carData *cData=(carData *) data;
	for(int i=0;i<cData->paths.size();i++){
		//cout<<cData->paths.size()<<"dasd"<<endl;
		usleep(cData->arriveTime*1000);
		writeOutput(0,cData->vehicleCode,cData->paths[i].intersectionCode,cData->paths[i].From,cData->paths[i].To);
		cData->crossroad->Enter(cData->vehicleCode,cData->paths[i].intersectionCode,cData->paths[i].From,cData->paths[i].To);
		usleep(cData->moveTime*1000);
		cData->crossroad->Exit(cData->vehicleCode,cData->paths[i].intersectionCode,cData->paths[i].From,cData->paths[i].To);
	}
	pthread_mutex_lock(&arabasayisimutexi);
	arabasayisi--;
	pthread_mutex_unlock(&arabasayisimutexi);
	pthread_exit(NULL);
}



CrossRoad::CrossRoad(int _N,int _mode){
	N=_N;
	lightState=new int[_N];
	if(_mode==0){
		for (int i = 0; i < N; ++i)
		{
			lightState[i]=0;
		}
	}
	else{
		for (int i = 0; i < N; ++i)
		{
			lightState[i]=-1;
		}
	}

	bekleyenler=new vector<string>[N];

	numCarfromEast=new int[N];
	numCarfromSouth=new int[N];
	numCarfromWest=new int[N];
	numCarfromNorth=new int[N];
	numCarFromWestToNorth=new int[N];
	numCarFromWestToSouth=new int[N];
	numCarFromWestToEast=new int[N];
	numCarFromEastToSouth=new int[N];
	numCarFromEastToWest=new int[N];
	numCarFromEastToNorth=new int[N];
	numCarFromSouthToEast=new int[N];
	numCarFromSouthToNorth=new int[N];
	numCarFromSouthToWest=new int[N];
	numCarFromNorthToEast=new int[N];
	numCarFromNorthToSouth=new int[N];
	numCarFromNorthToWest=new int[N];

	for (int i = 0; i < N; ++i)
	{
		numCarfromEast[i]=numCarfromSouth[i]=numCarfromWest[i]=numCarfromNorth[i]=0;
		numCarFromWestToNorth[i]=numCarFromWestToSouth[i]=numCarFromWestToEast[i]=0;
		numCarFromEastToSouth[i]=numCarFromEastToWest[i]=numCarFromEastToNorth[i]=0;
		numCarFromSouthToEast[i]=numCarFromSouthToNorth[i]=numCarFromSouthToWest[i]=0;
		numCarFromNorthToEast[i]=numCarFromNorthToSouth[i]=numCarFromNorthToWest[i]=0;
	}
	
	mutexforcv=new pthread_mutex_t[N];
	westgec=new pthread_cond_t[N];
	southgec=new pthread_cond_t[N];
	northgec=new pthread_cond_t[N];
	eastgec=new pthread_cond_t[N];

	westtonorth=new pthread_cond_t[N];
	westtoeast=new pthread_cond_t[N];
	westtosouth=new pthread_cond_t[N];

	southtowest=new pthread_cond_t[N];
	southtonorth=new pthread_cond_t[N];
	southtoeast=new pthread_cond_t[N];
	
	easttosouth=new pthread_cond_t[N];
	easttowest=new pthread_cond_t[N];
	easttonorth=new pthread_cond_t[N];

	northtoeast=new pthread_cond_t[N];
	northtowest=new pthread_cond_t[N];
	northtosouth=new pthread_cond_t[N];

	for (int i = 0; i < N; ++i)
	{
		pthread_mutex_init(&mutexforcv[i],NULL);
		pthread_cond_init(&westgec[i],NULL);
		pthread_cond_init(&southgec[i],NULL);
		pthread_cond_init(&northgec[i],NULL);
		pthread_cond_init(&eastgec[i],NULL);

		pthread_cond_init(&westtonorth[i],NULL);
		pthread_cond_init(&westtoeast[i],NULL);
		pthread_cond_init(&westtosouth[i],NULL);

		pthread_cond_init(&southtowest[i],NULL);
		pthread_cond_init(&southtonorth[i],NULL);
		pthread_cond_init(&southtoeast[i],NULL);

		pthread_cond_init(&easttosouth[i],NULL);
		pthread_cond_init(&easttowest[i],NULL);
		pthread_cond_init(&easttonorth[i],NULL);

		pthread_cond_init(&northtoeast[i],NULL);
		pthread_cond_init(&northtowest[i],NULL);
		pthread_cond_init(&northtosouth[i],NULL);
	}
	
}

void CrossRoad::Enter(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To){
//Vehicles call this function for entering the intersection
	//cout<<"girdi mi"<<endl;
	pthread_mutex_lock(&mutexforcv[intersectionCode]);
	//cout<<"enterladı"<<endl;
	if(lightState[intersectionCode]!=-1){
	if(From==WEST){
		if(lightState[intersectionCode]!=0 || numCarfromEast[intersectionCode]!=0 || numCarfromSouth[intersectionCode]!=0 || numCarfromNorth[intersectionCode]!=0){
			pthread_cond_wait(&westgec[intersectionCode],&mutexforcv[intersectionCode]);
		}
		numCarfromWest[intersectionCode]++;
		writeOutput(1,vehicleCode,intersectionCode,From,To);
	}
	else if(From==SOUTH){
		if(lightState[intersectionCode]!=1 || numCarfromEast[intersectionCode]!=0 || numCarfromWest[intersectionCode]!=0 || numCarfromNorth[intersectionCode]!=0){
			pthread_cond_wait(&southgec[intersectionCode],&mutexforcv[intersectionCode]);
		}
		numCarfromSouth[intersectionCode]++;
		writeOutput(1,vehicleCode,intersectionCode,From,To);
	}
	else if(From==EAST){
		if(lightState[intersectionCode]!=2 || numCarfromWest[intersectionCode]!=0 || numCarfromSouth[intersectionCode]!=0 || numCarfromNorth[intersectionCode]!=0){
			pthread_cond_wait(&eastgec[intersectionCode],&mutexforcv[intersectionCode]);
		}
		numCarfromEast[intersectionCode]++;
		writeOutput(1,vehicleCode,intersectionCode,From,To);
	}
	else if(From==NORTH){
		if(lightState[intersectionCode]!=3 || numCarfromEast[intersectionCode]!=0 || numCarfromSouth[intersectionCode]!=0 || numCarfromWest[intersectionCode]!=0){
			pthread_cond_wait(&northgec[intersectionCode],&mutexforcv[intersectionCode]);
		}
		numCarfromNorth[intersectionCode]++;
		writeOutput(1,vehicleCode,intersectionCode,From,To);
	}
	}else{
	if(From==WEST){//tamam
		if(To==EAST){
			if(numCarFromNorthToSouth[intersectionCode] != 0 || numCarFromNorthToEast[intersectionCode] != 0 || numCarFromEastToSouth[intersectionCode] !=0 || numCarfromSouth[intersectionCode] != 0) {
				bekleyenler[intersectionCode].push_back("westtoeast");
				pthread_cond_wait(&westtoeast[intersectionCode],&mutexforcv[intersectionCode]);//duz
			}else{
				numCarfromWest[intersectionCode]++;
				numCarFromWestToEast[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==NORTH){
			if(numCarfromEast[intersectionCode]!=0 || numCarfromSouth[intersectionCode]!=0 || numCarFromNorthToEast[intersectionCode]!=0 || numCarFromNorthToSouth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("westtonorth");
				pthread_cond_wait(&westtonorth[intersectionCode],&mutexforcv[intersectionCode]);//sol
			}else{
				numCarfromWest[intersectionCode]++;
				numCarFromWestToNorth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==SOUTH){
			if(numCarFromEastToSouth[intersectionCode]!=0 || numCarFromNorthToEast[intersectionCode]!=0 || numCarFromNorthToSouth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("westtosouth");
				pthread_cond_wait(&westtosouth[intersectionCode],&mutexforcv[intersectionCode]);//sag
			}else{
				numCarfromWest[intersectionCode]++;
				numCarFromWestToSouth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
	}
	else if(From==SOUTH){//tamam
		if(To==NORTH){
			if(numCarFromWestToNorth[intersectionCode]!=0 || numCarFromWestToEast[intersectionCode]!=0 || numCarFromNorthToEast[intersectionCode]!=0 || numCarfromEast[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("southtonorth");
				pthread_cond_wait(&southtonorth[intersectionCode],&mutexforcv[intersectionCode]);//duz
			}else{
				numCarfromSouth[intersectionCode]++;
				numCarFromSouthToNorth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==WEST){
			if(numCarfromNorth[intersectionCode]!=0 || numCarfromEast[intersectionCode]!=0 || numCarFromWestToEast[intersectionCode]!=0 || numCarFromWestToNorth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("southtowest");
				pthread_cond_wait(&southtowest[intersectionCode],&mutexforcv[intersectionCode]);//sag
			}else{
				numCarfromSouth[intersectionCode]++;
				numCarFromSouthToWest[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==EAST){
			if(numCarFromNorthToEast[intersectionCode]!=0 || numCarFromWestToEast[intersectionCode]!=0 || numCarFromWestToNorth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("southtoeast");
				pthread_cond_wait(&southtoeast[intersectionCode],&mutexforcv[intersectionCode]);//sol
			}else{
				numCarfromSouth[intersectionCode]++;
				numCarFromSouthToEast[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
	}
	else if(From==EAST){//tamam
		if(To==WEST){
			if(numCarFromSouthToNorth[intersectionCode]!=0 || numCarFromSouthToWest[intersectionCode]!=0 || numCarFromWestToNorth[intersectionCode]!=0 || numCarfromNorth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("easttowest");
				pthread_cond_wait(&easttowest[intersectionCode],&mutexforcv[intersectionCode]);//duz
			}else{
				numCarfromEast[intersectionCode]++;
				numCarFromEastToWest[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==SOUTH){
			if(numCarFromSouthToNorth[intersectionCode]!=0 || numCarFromSouthToWest[intersectionCode]!=0 || numCarfromNorth[intersectionCode]!=0 || numCarfromWest[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("easttosouth");
				pthread_cond_wait(&easttosouth[intersectionCode],&mutexforcv[intersectionCode]);//sag
			}else{
				numCarfromEast[intersectionCode]++;
				numCarFromEastToSouth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==NORTH){
			if(numCarFromWestToNorth[intersectionCode]!=0 || numCarFromSouthToWest[intersectionCode]!=0 || numCarFromSouthToNorth[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("easttonorth");
				pthread_cond_wait(&easttonorth[intersectionCode],&mutexforcv[intersectionCode]);//sol
			}else{
				numCarfromEast[intersectionCode]++;
				numCarFromEastToNorth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
	}
	else if(From==NORTH){//tamam
		if(To==SOUTH){
			if(numCarFromEastToWest[intersectionCode]!=0 || numCarFromEastToSouth[intersectionCode]!=0 || numCarFromSouthToWest[intersectionCode]!=0 || numCarfromWest[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("northtosouth");
				pthread_cond_wait(&northtosouth[intersectionCode],&mutexforcv[intersectionCode]);//duz
			}else{
				numCarfromNorth[intersectionCode]++;
				numCarFromNorthToSouth[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==EAST){
			if(numCarfromSouth[intersectionCode]!=0 || numCarfromWest[intersectionCode]!=0 || numCarFromEastToSouth[intersectionCode]!=0 || numCarFromSouthToWest[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("northtoeast");
				pthread_cond_wait(&northtoeast[intersectionCode],&mutexforcv[intersectionCode]);//sag
			}else{
				numCarfromNorth[intersectionCode]++;
				numCarFromNorthToEast[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
		else if(To==WEST){
			if(numCarFromSouthToWest[intersectionCode]!=0 || numCarFromEastToSouth[intersectionCode]!=0 || numCarFromEastToWest[intersectionCode]!=0){
				bekleyenler[intersectionCode].push_back("northtowest");
				pthread_cond_wait(&northtowest[intersectionCode],&mutexforcv[intersectionCode]);//sol
			}else{
				numCarfromNorth[intersectionCode]++;
				numCarFromNorthToWest[intersectionCode]++;
			}
			writeOutput(1,vehicleCode,intersectionCode,From,To);
		}
	}
	}
	pthread_mutex_unlock(&mutexforcv[intersectionCode]);
}
void CrossRoad::Exit(int vehicleCode, int intersectionCode, DIRECTION From,DIRECTION To){
//Vehicles call this function for exiting the intersection
	pthread_mutex_lock(&mutexforcv[intersectionCode]);
	if(lightState[intersectionCode]!=-1){
	if(From==WEST){
		numCarfromWest[intersectionCode]--;
		writeOutput(2,vehicleCode,intersectionCode,From,To);
		if(numCarfromWest[intersectionCode]==0){
			if(lightState[intersectionCode]==0){
				pthread_cond_broadcast(&westgec[intersectionCode]);
			}else if(lightState[intersectionCode]==1){
				pthread_cond_broadcast(&southgec[intersectionCode]);
			}else if(lightState[intersectionCode]==2){
				pthread_cond_broadcast(&eastgec[intersectionCode]);
			}else{
				pthread_cond_broadcast(&northgec[intersectionCode]);
			}
		}
	}
	else if(From==SOUTH){
		numCarfromSouth[intersectionCode]--;
		writeOutput(2,vehicleCode,intersectionCode,From,To);
		if(numCarfromSouth[intersectionCode]==0){
			if(lightState[intersectionCode]==0){
				pthread_cond_broadcast(&westgec[intersectionCode]);
			}else if(lightState[intersectionCode]==1){
				pthread_cond_broadcast(&southgec[intersectionCode]);
			}else if(lightState[intersectionCode]==2){
				pthread_cond_broadcast(&eastgec[intersectionCode]);
			}else{
				pthread_cond_broadcast(&northgec[intersectionCode]);
			}
		}
	}
	else if(From==EAST){
		numCarfromEast[intersectionCode]--;
		writeOutput(2,vehicleCode,intersectionCode,From,To);
		if(numCarfromEast[intersectionCode]==0){
			if(lightState[intersectionCode]==0){
				pthread_cond_broadcast(&westgec[intersectionCode]);
			}else if(lightState[intersectionCode]==1){
				pthread_cond_broadcast(&southgec[intersectionCode]);
			}else if(lightState[intersectionCode]==2){
				pthread_cond_broadcast(&eastgec[intersectionCode]);
			}else{
				pthread_cond_broadcast(&northgec[intersectionCode]);
			}
		}
	}
	else if(From==NORTH){
		numCarfromNorth[intersectionCode]--;
		writeOutput(2,vehicleCode,intersectionCode,From,To);
		if(numCarfromNorth[intersectionCode]==0){
			if(lightState[intersectionCode]==0){
				pthread_cond_broadcast(&westgec[intersectionCode]);
			}else if(lightState[intersectionCode]==1){
				pthread_cond_broadcast(&southgec[intersectionCode]);
			}else if(lightState[intersectionCode]==2){
				pthread_cond_broadcast(&eastgec[intersectionCode]);
			}else{
				pthread_cond_broadcast(&northgec[intersectionCode]);
			}
		}
	}
	}else{
	if(From==SOUTH){//tamam
		if (To==WEST){
			numCarfromSouth[intersectionCode]--;
			numCarFromSouthToWest[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromSouthToWest[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtowest"){
						if(numCarFromSouthToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromEastToWest[intersectionCode]==0){
							pthread_cond_signal(&northtowest[intersectionCode]);//sol
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromSouthToNorth[intersectionCode]==0){
							pthread_cond_signal(&easttonorth[intersectionCode]);//sol
							numCarfromEast[intersectionCode]++;
							numCarFromEastToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}	
			}
		}
		else if(To==NORTH){
			numCarfromSouth[intersectionCode]--;
			numCarFromSouthToNorth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if (numCarFromSouthToNorth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromSouthToNorth[intersectionCode]==0){
							pthread_cond_signal(&easttonorth[intersectionCode]);//sol
							numCarfromEast[intersectionCode]++;
							numCarFromEastToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==EAST){
			numCarfromSouth[intersectionCode]--;
			numCarFromSouthToEast[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromSouthToEast[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					/*if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}///SİLDİN*/
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
	}
	else if(From==WEST){//tamam
		if(To==NORTH){
			numCarfromWest[intersectionCode]--;
			numCarFromWestToNorth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromWestToNorth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromSouthToNorth[intersectionCode]==0){
							pthread_cond_signal(&easttonorth[intersectionCode]);//sol
							numCarfromEast[intersectionCode]++;
							numCarFromEastToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtoeast"){
						if(numCarFromNorthToEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtoeast[intersectionCode]);//sol
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==EAST){
			numCarfromWest[intersectionCode]--;
			numCarFromWestToEast[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromWestToEast[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtoeast"){
						if(numCarFromNorthToEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtoeast[intersectionCode]);//sol
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==SOUTH){
			numCarfromWest[intersectionCode]--;
			numCarFromWestToSouth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if (numCarFromWestToSouth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					/*if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}//sildin*/
				}
			}
		}
	}
	else if(From==NORTH){//tamam
		if(To==EAST){
			numCarfromNorth[intersectionCode]--;
			numCarFromNorthToEast[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromNorthToEast[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtoeast"){
						if(numCarFromNorthToEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtoeast[intersectionCode]);//sol
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtosouth"){
						if(numCarFromEastToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtosouth[intersectionCode]);//sag
							numCarfromWest[intersectionCode]++,
							numCarFromWestToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==SOUTH){
			numCarfromNorth[intersectionCode]--;
			numCarFromNorthToSouth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromNorthToSouth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtosouth"){
						if(numCarFromEastToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtosouth[intersectionCode]);//sag
							numCarfromWest[intersectionCode]++,
							numCarFromWestToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==WEST){
			numCarfromNorth[intersectionCode]--;
			numCarFromNorthToWest[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromNorthToWest[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="easttowest"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0){
							pthread_cond_signal(&easttowest[intersectionCode]);//duz
							numCarfromEast[intersectionCode]++;
							numCarFromEastToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					/*if(bekleyenler[intersectionCode][i]=="easttosouth"){
						if(numCarFromSouthToNorth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&easttosouth[intersectionCode]);//sag
							numCarfromEast[intersectionCode]++;
							numCarFromEastToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}//sildin*/
				}
			}
		}
	}
	else if(From==EAST){//tamam
		if (To==SOUTH){
			numCarfromEast[intersectionCode]--;
			numCarFromEastToSouth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromEastToSouth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="westtoeast"){
						if(numCarFromNorthToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0){
							pthread_cond_signal(&westtoeast[intersectionCode]);//duz
							numCarfromWest[intersectionCode]++;
							numCarFromWestToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
						
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtosouth"){
						if(numCarFromEastToSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtosouth[intersectionCode]);//sag
							numCarfromWest[intersectionCode]++,
							numCarFromWestToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtowest"){
						if(numCarFromSouthToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode] ==0 && numCarFromEastToWest[intersectionCode]==0){
							pthread_cond_signal(&northtowest[intersectionCode]);//sol
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==WEST){
			numCarfromEast[intersectionCode]--;
			numCarFromEastToWest[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromEastToWest[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="northtosouth"){
						if(numCarFromEastToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0 && numCarfromWest[intersectionCode]==0){
							pthread_cond_signal(&northtosouth[intersectionCode]);//duz
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToSouth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtoeast"){
						if(numCarfromSouth[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode]==0 && numCarFromSouthToWest[intersectionCode]==0){
							pthread_cond_signal(&northtoeast[intersectionCode]);//sag
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToEast[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="northtowest"){
						if(numCarFromSouthToWest[intersectionCode]==0 && numCarFromEastToSouth[intersectionCode] ==0 && numCarFromEastToWest[intersectionCode]==0){
							pthread_cond_signal(&northtowest[intersectionCode]);//sol
							numCarfromNorth[intersectionCode]++;
							numCarFromNorthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
				}
			}
		}
		else if(To==NORTH){
			numCarfromEast[intersectionCode]--;
			numCarFromEastToNorth[intersectionCode]--;
			writeOutput(2,vehicleCode,intersectionCode,From,To);
			if(numCarFromEastToNorth[intersectionCode]==0){
				for(int i=0;i<bekleyenler[intersectionCode].size();i++){
					if(bekleyenler[intersectionCode][i]=="westtonorth"){
						if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarFromNorthToSouth[intersectionCode]==0){
							pthread_cond_signal(&westtonorth[intersectionCode]);//sol
							numCarfromWest[intersectionCode]++;
							numCarFromWestToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					if(bekleyenler[intersectionCode][i]=="southtonorth"){
						if(numCarFromWestToNorth[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromNorthToEast[intersectionCode]==0 && numCarfromEast[intersectionCode]==0){
							pthread_cond_signal(&southtonorth[intersectionCode]);//duz
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToNorth[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}
					/*if(bekleyenler[intersectionCode][i]=="southtowest"){
						if(numCarfromNorth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0 && numCarFromWestToEast[intersectionCode]==0 && numCarFromWestToNorth[intersectionCode]==0){
							pthread_cond_signal(&southtowest[intersectionCode]);//sag
							numCarfromSouth[intersectionCode]++;
							numCarFromSouthToWest[intersectionCode]++;
							bekleyenler[intersectionCode].erase(bekleyenler[intersectionCode].begin()+i);
							i--;
							continue;
						}
					}///sildin*/
				}
			}
		}
	}
	}
	pthread_mutex_unlock(&mutexforcv[intersectionCode]);
}
void CrossRoad::SetGreenLight(int intersectionCode){
//Call this function for turning green traffic lights on in the given intersection
	//cout<<"yok artik amk"<<endl;
	pthread_mutex_lock(&mutexforcv[intersectionCode]);
	if(lightState[intersectionCode]==0){
		lightState[intersectionCode]=1;
		writeOutput(3,-1,intersectionCode,SOUTH,SOUTH);
		if(numCarfromEast[intersectionCode]==0 && numCarfromWest[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0)
			pthread_cond_broadcast(&southgec[intersectionCode]);
	}
	else if(lightState[intersectionCode]==1){
		lightState[intersectionCode]=2;
		writeOutput(3,-1,intersectionCode,EAST,EAST);
		if(numCarfromWest[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0)
			pthread_cond_broadcast(&eastgec[intersectionCode]);
	}
	else if(lightState[intersectionCode]==2){
		lightState[intersectionCode]=3;
		writeOutput(3,-1,intersectionCode,NORTH,NORTH);
		if(numCarfromWest[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarfromEast[intersectionCode]==0)
			pthread_cond_broadcast(&northgec[intersectionCode]);
	}
	else if(lightState[intersectionCode]==3){
		lightState[intersectionCode]=0;
		writeOutput(3,-1,intersectionCode,WEST,WEST);
		if(numCarfromEast[intersectionCode]==0 && numCarfromSouth[intersectionCode]==0 && numCarfromNorth[intersectionCode]==0)
			pthread_cond_broadcast(&westgec[intersectionCode]);
	}
	pthread_mutex_unlock(&mutexforcv[intersectionCode]);
}

int main(int argc,char* argv[]){
	//n mode duration
	pthread_mutex_init(&arabasayisimutexi,NULL);
	int N=atoi(string(argv[1]).c_str()),mode=atoi(string(argv[2]).c_str()),duration=atoi(string(argv[3]).c_str());
	//cout<<N <<" "<<mode <<" "<<duration<<endl;
	CrossRoad crossroad(N+1,mode);
	if(mode==0){
		//pthread_t t1;
		for(int i=1;i<N+1;i++){
			//cout<<N+1 <<" tane isik yarattim"<<endl;
			pthread_t pid;
			intersectionData *iData=new intersectionData;
			iData->intersectionCode=i;
			iData->duration=duration;
			iData->crossroad=&crossroad;
			pthread_attr_t onur;
			pthread_attr_init(&onur);
			pthread_attr_setdetachstate(&onur,PTHREAD_CREATE_DETACHED);
			pthread_create(&pid,&onur,trafficLight,(void *)iData);
			pthread_detach(pid);
		}
	}
	//cout<<"isiklar tamam"<<endl;
	vector<carData*> cars;
	carData *cData;
	pathData *pData;
	string line;
	int flag1=1,flag2=0;
	char *pch;
	getline(cin,line);
	while(1){
		if(cin.eof()){break;}
		if(flag1){
			cData=new carData;
		}
		if(!flag2){
			pData=new pathData;
		}
		char * writable = new char[line.size() + 1];
        copy(line.begin(),line.end(),writable);
        writable[line.size()] = '\0';
        char * pch;
        pch=strtok(writable," ");
		while ((pch) != NULL)
		{
			if(flag1){
				// ilk satırı al		
				if(flag2==0){
					cData->vehicleCode=atoi((const char*)pch);
					flag2++;
					goto d;
				}else if(flag2==1){
					cData->arriveTime=atoi((const char*)pch);
					flag2++;
					goto d;
				}
				else{
					cData->moveTime=atoi((const char*)pch);
					cData->crossroad=&crossroad;
					flag2=0;
					goto d;
				}
			}
			else if(string(pch)=="NR"){
				cars.push_back(cData);
				flag1=1;
				pthread_t cid;
				pthread_attr_t onur;
				pthread_attr_init(&onur);
				pthread_attr_setdetachstate(&onur,PTHREAD_CREATE_DETACHED);
				pthread_create(&cid,&onur,car,(void *)cData);
				pthread_detach(cid);
				pthread_mutex_lock(&arabasayisimutexi);
				arabasayisi++;
				pthread_mutex_unlock(&arabasayisimutexi);
				goto c;
			}else{
				if(flag2==0){
					pData->intersectionCode=atoi((const char*)pch);
					flag2++;
					goto d;
				}else if(flag2==1){
					if(string(pch)=="WEST"){
						pData->From=WEST;
					}
					else if(string(pch)=="SOUTH"){
						pData->From=SOUTH;
					}
					else if(string(pch)=="EAST"){
						pData->From=EAST;
					}
					else{
						pData->From=NORTH;
					}
					flag2++;
					goto d;
				}
				else{
					if(string(pch)=="WEST"){
						pData->To=WEST;
					}
					else if(string(pch)=="SOUTH"){
						pData->To=SOUTH;
					}
					else if(string(pch)=="EAST"){
						pData->To=EAST;
					}
					else{
						pData->To=NORTH;
					}
					cData->paths.push_back(*pData);
					flag2=0;
					goto d;
				}
			}
		  d:pch = strtok (NULL, " ");
		}
		if(flag1){flag1=0;}
	  c:getline(cin,line);
	}

	
	/*arabasayisi=cars.size();
	pthread_t *cids=new pthread_t[cars.size()];
	//cout<<"arac sayisi "<<cars.size()<<endl;
	for(int i=0;i<cars.size();i++){
		//cout<<"arac sayisi "<<cars.size()<<endl;
		/*cout<<cars[i]->vehicleCode<<" "<<cars[i]->arriveTime<< " "<< cars[i]->moveTime <<endl;
		for (int j = 0; j < cars[i]->paths.size(); ++j)
		{
			cout<<cars[i]->paths[j].intersectionCode<<" "<<cars[i]->paths[j].From<<" "<<cars[i]->paths[j].To<<endl;
		
		}
		pthread_attr_t onur;
		pthread_attr_init(&onur);
		pthread_attr_setdetachstate(&onur,PTHREAD_CREATE_DETACHED);
		pthread_create(&cids[i],&onur,car,(void *)cars[i]);
		pthread_detach(cids[i]);
	}
*/
	



	//pthread_create(&t1,NULL,trafficLight,(void *)iData1);
	//cout<<"olusturdu"<<endl;
	//pthread_detach(t1);
	/*pthread_create(&t2,NULL,car,(void *)cData1);
	pthread_detach(t2);
	pthread_create(&t3,NULL,car,(void *)cData2);
	pthread_detach(t3);
	pthread_create(&t4,NULL,car,(void *)cData3);
	pthread_detach(t4);
	pthread_create(&t5,NULL,car,(void *)cData4);
	pthread_detach(t5);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	pthread_join(t4,NULL);
	pthread_join(t5,NULL);*/
	//pthread_join(t1,NULL);
	//cout<<"bitti"<<endl;
	while(arabasayisi!=0);
	//pthread_exit(NULL);
	pthread_mutex_lock(&mutexWrite);
	return 0;
	//for (int i = 1; i < N+1; ++i)
	//{
	//	pthread_cancel(pids[i]);
	//}
}
