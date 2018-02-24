#include "FileHelper.h"
#include "Parameters.h"
#include <fstream>
#include <windows.h>
#include <iomanip>
#include <chrono>
#include <iostream>
#include <experimental/filesystem>

using namespace parameters;
using namespace std;

FileHelper::FileHelper()
{
}


FileHelper::~FileHelper()
{
}


void FileHelper::createDirectory(const string name)
{
	if (!CreateDirectory(name.c_str(), nullptr))
	{
		const string msg("Error creating the directory: " + name + "\n");
		throw runtime_error(msg);
	}
}

void FileHelper::createDirectories(const string name, double time[])
{
	try
	{
		createDirectory(name);
		for (auto t = 0; t < sizeof(time) + 1; t++)
		{
			const string folder = "0" + to_string(int(time[t] * 10));
			createDirectory(name + "//" + folder);
			createDirectory(name + "//" + folder + "//methods");
		}
		createDirectory(name + "//final errors");
		createDirectory(name + "//final norms");
		createDirectory(name + "//final solution");
	}
	catch (exception& e)
	{
		cout << e.what();
	}
}

void FileHelper::removeDirectory(const string name)
{
	try
	{
		experimental::filesystem::remove_all(name.c_str());
	}
	catch (experimental::filesystem::filesystem_error e)
	{
		cout << e.what() << '\n';
	}
}


void FileHelper::describeDataInFile(ofstream& file, const string name, ComputionalMethod* cm, const double time[])
{
	file << name << endl << "Time in rows. Values: ";
	for (auto i = 0; i < sizeof(time) + 1; i++)
	{
		file << time[i] << "; ";
	}
	file << endl << "Space in columns. Values:" << endl;
	for (int i = 0; i < cm->getSpaceGrid() + 2; i++)
	{
		file << cm->getX()[i] << " ";
	}
	file << endl;
}

void FileHelper::describeDataInFile(ofstream& file, const string desc, const string name, const double time[])
{
	file << name << endl << "Time in rows. Values: ";
	for (auto i = 0; i < sizeof(time) + 1; i++)
	{
		file << time[i] << "; ";
	}
	file << endl << desc << endl;
}

void FileHelper::printResultsToFileForAllTimes(const string path, const string name, ComputionalMethod* cm,
                                               const double time[], const double currentTime, const bool firstTime)
{
	ofstream file;
	if (firstTime)
	{
		file.open(path);
		describeDataInFile(file, name, cm, time);
	}
	else
	{
		file.open(path, fstream::app);
	}
	file << fixed << setprecision(8);
	for (int t = 0; t < cm->getTimeGrid() + 2; t++)
	{
		if (cm->doubleEquals(cm->getY()[t], currentTime))
		{
			for (int i = 0; i < cm->getSpaceGrid() + 2; i++)
			{
				file << cm->getT()[t][i] << "\t";
			}
			file << endl;
		}
	}
	file.close();
}


void FileHelper::printErrorsToFileForAllTimes(const string path, const string name, Numerical* numerical,
                                              const double time[], const double currentTime, const bool firstTime)
{
	ofstream file;
	if (firstTime)
	{
		file.open(path);
		describeDataInFile(file, name, numerical, time);
	}
	else
	{
		file.open(path, fstream::app);
	}

	file << fixed << setprecision(8);
	for (int t = 0; t < numerical->getTimeGrid() + 2; t++)
	{
		if (numerical->doubleEquals(numerical->getY()[t], currentTime))
		{
			for (int i = 0; i < numerical->getSpaceGrid() + 2; i++)
			{
				file << numerical->getErrors()[i] << "\t";
			}
			file << endl;
		}
	}
	file.close();
}

void FileHelper::printResultsForAllMethodsToFile(const string path, Analytical* analytical, Numerical** numerical,
                                                 const double time)
{
	ofstream file;
	file.open(path);
	file << fixed << setprecision(8);
	for (auto t = 0; t < analytical->getTimeGrid() + 2; t++)
	{
		if (analytical->doubleEquals(analytical->getY()[t], time))
		{
			file << "Final results for all the methods." << endl;
			file << "Time: " << time << endl <<
				"Space\t\t\t Analytical\t\t DuFortFrankel\t\t Richardson\t\t Laasonen\t\t CrankNicholson" << endl;
			for (auto i = 0; i < analytical->getSpaceGrid() + 2; i++)
			{
				file << analytical->getX()[i] << "\t\t" << analytical->getT()[t][i];
				for (auto k = 0; k < sizeof(numerical); k++)
				{
					file << "\t\t" << numerical[k]->getT()[t][i];
				}
				file << endl;
			}
		}
	}
	file.close();
}

void FileHelper::printErrorsToFile(const string path, Numerical** numerical, const double time, const bool isTask1)
{
	const string desc = isTask1
		                    ? "Space\t DuFord-Freknel\t Richardson\t Laasonen\t Crank-Nicholson"
		                    : "Delat t = 0.010\t Delat t = 0.025\t Delat t = 0.050\t Delat t = 0.100\t ";

	ofstream file;
	file.open(path);
	file << fixed << setprecision(8);
	for (int t = 0; t < numerical[0]->getTimeGrid() + 2; t++)
	{
		if (numerical[0]->doubleEquals(numerical[0]->getY()[t], time))
		{
			file << "Final errors." << endl << "Time: " << time << endl << desc << endl;
			for (int i = 0; i < numerical[0]->getSpaceGrid() + 2; i++)
			{
				file << numerical[0]->getX()[i];
				for (int k = 0; k < sizeof(numerical); k++)
				{
					file << "\t\t" << numerical[k]->getErrors()[i];
				}
				file << endl;
			}
		}
	}
	file.close();
}

void FileHelper::printNormToFile(const string path, const string name, const string desc, Numerical** numerical,
                                 const int normNo, const double time[], const double currentTime, const bool firstTime)
{
	ofstream file;
	if (firstTime)
	{
		file.open(path);
		describeDataInFile(file, desc, name, time);
	}
	else
	{
		file.open(path, fstream::app);
	}
	file << fixed << setprecision(8);
	for (int t = 0; t < numerical[0]->getTimeGrid() + 2; t++)
	{
		if (numerical[0]->doubleEquals(numerical[0]->getY()[t], currentTime))
		{
			for (int k = 0; k < sizeof(numerical); k++)
			{
				switch (normNo)
				{
				case 1:
					file << numerical[k]->getOneNorm() << "\t";
					break;
				case 2:
					file << numerical[k]->getTwoNorm() << "\t";
					break;
				case 3:
					file << numerical[k]->getUniformNorm() << "\t";
					break;
				default:
					break;
				}
			}
			file << endl;
		}
	}
	file.close();
}

void FileHelper::printNormsToFileForAllTimes(const string path, Numerical** numerical, const double time[],
                                             const double currentTime, const bool firstTime, const bool isTask1)
{
	const string desc = isTask1
		                    ? "DuFord-Freknel\t Richardson\t Laasonen\t Crank-Nicholson"
		                    : "Delat t = 0.010\t Delat t = 0.025\t Delat t = 0.050\t Delat t = 0.100\t ";
	const int normsSize = 3;
	string norms[normsSize] = {"1-Norm", "2-Norm", "Uniform-Norm"};
	for (auto i = 0; i < normsSize; ++i)
	{
		const string fileName = "Final " + norms[i] + " for all the methods.txt";
		printNormToFile(path + fileName, fileName, desc, numerical, i + 1, time, currentTime, firstTime);
	}
}

void FileHelper::printComputationalTimeToFileForAllTimes(const string path,
                                                         chrono::duration<double> conputationalTime[],
                                                         const double time[], const bool firstTime)
{
	ofstream file;
	if (firstTime)
	{
		const string fileName = "Computational times for Lassonen methods with different delta t.";
		const string desc = "Delat t = 0.010\t Delat t = 0.025\t Delat t = 0.050\t Delat t = 0.100\t ";
		file.open(path);
		describeDataInFile(file, desc, fileName, time);
	}
	else
	{
		file.open(path, fstream::app);
	}
	file << fixed << setprecision(8);

	for (auto i = 0; i < sizeof(conputationalTime); i++)
	{
		file << conputationalTime[i].count() << "\t";
	}

	file << endl;
	file.close();
}

void FileHelper::printLaasonenResultsForAllDtToFile(const string path, Analytical* analytical, Numerical** numerical,
                                                    const double time, const double timeStepSize[])
{
	const string fileName = "Final results for Lassonen methods with different delta t for time " + to_string(time) +
		".txt";
	ofstream file;
	file.open(path);
	file << fixed << setprecision(8);

	file << fileName << endl << "Method in rows. Analytical; Laasonen delta t = ";
	for (auto i = 0; i < sizeof(timeStepSize); i++)
	{
		file << timeStepSize[i] << "; ";
	}

	file << endl << "Space in columns. Values: " << endl;
	for (int i = 0; i < analytical->getSpaceGrid() + 2; i++)
	{
		file << analytical->getX()[i] << " ";
	}
	file << endl;

	for (auto t = 0; t < analytical->getTimeGrid() + 2; t++)
	{
		if (analytical->doubleEquals(analytical->getY()[t], time))
		{
			for (int i = 0; i < analytical->getSpaceGrid() + 2; i++)
			{
				file << analytical->getT()[t][i] << " ";
			}
		}
	}
	file << endl;
	for (int k = 0; k < sizeof(numerical); k++)
	{
		for (int t = 0; t < numerical[k]->getTimeGrid() + 2; t++)
		{
			if (numerical[k]->doubleEquals(numerical[k]->getY()[t], time))
			{
				for (int i = 0; i < numerical[k]->getSpaceGrid() + 2; i++)
				{
					file << numerical[k]->getT()[t][i] << " ";
				}
				file << endl;
			}
		}
	}
	file.close();
}
