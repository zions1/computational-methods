#include "Parameters.h"
#include "Analytical.h"
#include "DuFortFrankel.h"
#include "Richardson.h"
#include "Laasonen.h"
#include "CrankNicholson.h"
#include <iomanip>
#include "FileHelper.h"
#include <ctime>
#include <chrono>

using namespace std;
using namespace parameters;

/**
 * Finds the solution for the first task.
 */
void solveFirstIssue()
{
	const string task = "TASK1";
	const string mainPath = task + "/";
	const auto size = 4;
	const auto timeSize = 5;
	double time[timeSize] = {0.1, 0.2, 0.3, 0.4, 0.5};
	FileHelper::removeDirectory(task);
	FileHelper::createDirectories(task, time);
	bool firstTime = true;

	auto analytical = new Analytical;
	const auto numerical = new Numerical*[size];
	numerical[0] = new DuFortFrankel;
	numerical[1] = new Richardson;
	numerical[2] = new Laasonen;
	numerical[3] = new CrankNicholson;


	for (auto t = 0; t < timeSize; t++)
	{
		const string timeNo = "0" + to_string(int(time[t] * 10));
		analytical->solveSolution(time[t]);
		string path = mainPath + timeNo + "/methods/" + analytical->getClassName() + ".txt";
		analytical->printResultToFile(path, time[t]);
		path = mainPath + "/final solutions/" + analytical->getClassName() + " solution for all times.txt";
		FileHelper::printResultsToFileForAllTimes(path, analytical->getClassName(), analytical, time, time[t], firstTime);

		for (auto i = 0; i < size; i++)
		{
			numerical[i]->solve();
			numerical[i]->calculateErrors(analytical->getT(), time[t]);
			path = mainPath + timeNo + "/methods/" + numerical[i]->getClassName() + ".txt";
			numerical[i]->printBasicResultToFile(path, numerical[i]->getClassName(), analytical->getT(), time[t]);
			path = mainPath + "final solutions/" + numerical[i]->getClassName() + " solution for all times.txt";
			FileHelper::printResultsToFileForAllTimes(path, numerical[i]->getClassName(), numerical[i], time, time[t],
			                                          firstTime);
			path = mainPath + "final errors/" + numerical[i]->getClassName() + " errors for all times.txt";
			FileHelper::printErrorsToFileForAllTimes(path, numerical[i]->getClassName(), numerical[i], time, time[t], firstTime);
		}
		path = mainPath + timeNo + "/Final results for all the methods.txt";
		FileHelper::printResultsForAllMethodsToFile(path, analytical, numerical, time[t]);
		path = mainPath + timeNo + "/Final errors for all the methods.txt";
		FileHelper::printErrorsToFile(path, numerical, time[t], true);
		path = mainPath + "final norms/";
		FileHelper::printNormsToFileForAllTimes(path, numerical, time, time[t], firstTime, true);
		firstTime = false;
	}
	delete analytical;	
	for (auto i = 0; i < sizeof(numerical); ++i)
	{
		delete numerical[i];
	}
	delete[] numerical;
}

/**
* Finds the solution for the second task.
*/
void solveSecondIssue()
{
	const string task = "TASK2";
	const string mainPath = task + "/";
	const auto timeSize = 5;
	const double deltaX = 0.05;
	double time[timeSize] = {0.1, 0.2, 0.3, 0.4, 0.5};
	const auto size = 4;
	double timeStepSize[size] = {0.01, 0.025, 0.05, 0.1};
	chrono::duration<double> computationalTime[size];
	FileHelper::removeDirectory(task);
	FileHelper::createDirectories(task, time);
	bool firstTime = true;

	const auto numerical = new Numerical*[size];
	for (auto i = 0; i < size; i++)
	{
		numerical[i] = new Laasonen(timeStepSize[i], deltaX);
	}
	auto analytical = new Analytical;

	for (auto t = 0; t < timeSize; t++)
	{
		const string timeNo = "0" + to_string(int(time[t] * 10));
		for (auto i = 0; i < size; i++)
		{
			auto tempAnalitycial = new Analytical(timeStepSize[i], deltaX);
			tempAnalitycial->solveSolution(time[t]);
			const chrono::high_resolution_clock::time_point beginTime = chrono::high_resolution_clock::now();
			numerical[i]->solve();
			const chrono::high_resolution_clock::time_point endTime = chrono::high_resolution_clock::now();
			computationalTime[i] = chrono::duration_cast<chrono::duration<double>>(endTime - beginTime);

			numerical[i]->calculateErrors(tempAnalitycial->getT(), time[t]);
			const string dt = " for time step " + to_string(numerical[i]->getDt()).substr(0, 5);
			string path = mainPath + timeNo + "/methods/" + numerical[i]->getClassName() + " for time step " + dt + ".txt";
			numerical[i]->printBasicResultToFile(path, numerical[i]->getClassName() + " for time step " + dt,
			                                     tempAnalitycial->getT(), time[t]);
			path = mainPath + "final solutions/" + numerical[i]->getClassName() + dt + " solution for all times.txt";
			FileHelper::printResultsToFileForAllTimes(path, numerical[i]->getClassName() + " deltaT " + dt, numerical[i], time,
			                                          time[t], firstTime);
			path = mainPath + "final errors/" + numerical[i]->getClassName() + dt + " errors for all times.txt";
			FileHelper::printErrorsToFileForAllTimes(path, numerical[i]->getClassName() + " deltaT " + dt, numerical[i], time,
			                                         time[t], firstTime);
			delete tempAnalitycial;
		}
		analytical->solveSolution(time[t]);
		string path = mainPath + timeNo + "/Final results for Lassonen methods with different delta t.txt";
		FileHelper::printLaasonenResultsForAllDtToFile(path, analytical, numerical, time[t], timeStepSize);
		path = mainPath + timeNo + "/Final errors for Lassonen methods with different delta t.txt";
		FileHelper::printErrorsToFile(path, numerical, time[t], false);
		path = mainPath + "final norms/";
		FileHelper::printNormsToFileForAllTimes(path, numerical, time, time[t], firstTime, false);
		path = mainPath + "/Computational times for Lassonen methods with different delta t.txt";
		FileHelper::printComputationalTimeToFileForAllTimes(path, computationalTime, time, firstTime);

		firstTime = false;
	}
	delete analytical;	
	for (auto i = 0; i < sizeof(numerical); ++i)
	{
		delete numerical[i];
	}
	delete[] numerical;
}


int main()
{
	solveFirstIssue();
	solveSecondIssue();
	return 0;
}
