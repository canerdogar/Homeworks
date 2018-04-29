#include <string>
const std::string directionName[4] = {"west", "south", "east", "north"};

pthread_mutex_t mutexWrite;// This mutex is used for atomic write operation

void writeOutput(int action, int vehicleCode, int intersectionCode, DIRECTION from, DIRECTION to)
{									
	// Set the appropriate parameters for the corresponding output. Output order is important so be sure you call this function in the correct step.
	
	pthread_mutex_lock(&mutexWrite);

	if(action == 0)//This will be called before the enter function is called
	{
		std::cout << "Vehicle = " << vehicleCode << " arrived the intersection " << intersectionCode << " from " << directionName[from] << " towards the " << directionName[to] << std::endl;
	}
	if(action == 1)//This will be called when the vehicle enters the intersection
	{
		std::cout << "Vehicle = " << vehicleCode << " entered the intersection " << intersectionCode << " from " << directionName[from] << " towards the " << directionName[to] << std::endl;
	}
	else if(action == 2)//This will be called when the vehicle leaves the intersection
	{
		std::cout << "Vehicle = " << vehicleCode << " exited the intersection " << intersectionCode << " from " << directionName[from] << " towards the " << directionName[to] << std::endl;
	}
	else if(action == 3)//This will be called when the green light turns on in the given direction of the given intersection. Take the value of "to" same with the value of "from" and set vehicle code as -1.
	{
		std::cout << "Green Light becomes active on the "<< directionName[from] << " incoming direction of the intersection " << intersectionCode << std::endl;
	}

	pthread_mutex_unlock(&mutexWrite);
}
