#pragma once
#include "Analytical.h"
#include "Numerical.h"
#include <chrono>
#include <string>

using namespace std;

/***
 * A FileHelper class for printing data to file.
 */
class FileHelper
{
public:
	/**
	* Default constructor.
	*/
	FileHelper();

	/**
	* Default destructor.
	*/
	~FileHelper();

	/**
	 * Create the directories hierarchy.
	 * \param name The name of the main direcotry.
	 * \param time The array of the time intervals.
	 */
	static void createDirectories(const string name, double time[]);

	/**
	* Remove the directory.
	* \param name The name of the main direcotry.
	*/
	static void removeDirectory(const string name);

	/**
	* Print results to the file for all time intervals.
	* \param path The path to the file.
	* \param name The name of the file.
	* \param cm The computational method pointer.
	* \param time The array of the time intervals.
	* \param currentTime The current time of the time intervals.
	* \param firstTime True if it is first time, false if not.
	*/
	static void printResultsToFileForAllTimes(const string path, const string name, ComputionalMethod* cm,
	                                          const double time[], const double currentTime, const bool firstTime);
	/**
	* Print errors to the file for all time intervals.
	* \param path The path to the file.
	* \param name The name of the file.
	* \param numerical The numerical method pointer.
	* \param time The array of the time intervals.
	* \param currentTime The current time of the time intervals.
	* \param firstTime True if it is first time, false if not.
	*/
	static void printErrorsToFileForAllTimes(const string path, const string name, Numerical* numerical,
	                                         const double time[], const double currentTime, const bool firstTime);
	/**
	* Print results to the file for all methods.
	* \param path The path to the file.
	* \param analytical The analytical method pointer.
	* \param numerical The array which contains the numerical method pointer.
	* \param time The array of the time intervals.
	*/
	static void printResultsForAllMethodsToFile(const string path, Analytical* analytical, Numerical** numerical,
	                                            const double time);
	/**
	* Print errors to the file.
	* \param path The path to the file.
	* \param numerical The array which contains the numerical method pointer.
	* \param time he current time of the time intervals.
	* \param isTask1 True if it is task no 1, false if not.
	*/
	static void printErrorsToFile(const string path, Numerical** numerical, const double time, const bool isTask1);
	/**
	* Print norms to the file for all times intervals.
	* \param path The path to the file.
	* \param numerical The array  of the numerical method pointer.
	* \param time The array of the time intervals.
	* \param currentTime The current time of the time intervals.
	* \param isTask1 True if it is task no 1, false if not.
	* \param firstTime True if it is first time, false if not.
	*/
	static void printNormsToFileForAllTimes(const string path, Numerical** numerical, const double time[],
	                                        const double currentTime, const bool firstTime, const bool isTask1);
	/**
	* Print computational times to the file for all times intervals.
	* \param path The path to the file.
	* \param conputationalTime The array of the computational times.
	* \param time The array of the time intervals.
	* \param firstTime True if it is first time, false if not.
	*/
	static void printComputationalTimeToFileForAllTimes(const string path, chrono::duration<double> conputationalTime[],
	                                                    const double time[], const bool firstTime);

	/**
	* Print the Laasonen results to the file for all time steps sizes.
	* \param path The path to the file.
	* \param analytical The analytical method pointer.
	* \param numerical The array of the numerical method pointer.
	* \param time The current time of the time intervals.
	* \param timeStepSize The array of the time steps sizes values.
	*/
	static void printLaasonenResultsForAllDtToFile(const string path, Analytical* analytical, Numerical** numerical,
	                                               const double time, const double timeStepSize[]);
private:
	/**
	* Creates a directory.
	* \param name The name of the directory.
	* \throws runtime_error exception when unable to create the direcory.
	*/
	static void createDirectory(const string name);

	/**
	* Descibe the data to file.
	* \param file The instance of the file.
	* \param name The information to write to the file.
	* \param cm The computational method pointer.
	* \param time The array of the time intervals.
	*/
	static void describeDataInFile(ofstream& file, const string name, ComputionalMethod* cm, const double time[]);
	/**
	* Descibe the data to file.
	* \param file The instance of the file.
	* \param desc The information to write to the file.
	* \param name The information to write to the file.
	* \param time The array of the time intervals.
	*/
	static void describeDataInFile(ofstream& file, const string desc, const string name, const double time[]);
	/**
	* Print results to the file for all time intervals.
	* \param path The path to the file.
	* \param name The name of the file.
	* \param desc The information to write to the file.
	* \param numerical The array which contains the numerical method pointer.
	* \param normNo The number of the norm.
	* \param time The array of the time intervals.
	* \param currentTime The current time of the time intervals.
	* \param firstTime True if it is first time, false if not.
	*/
	static void printNormToFile(const string path, const string name, const string desc, Numerical** numerical,
		const int normNo, const double time[], const double currentTime, const bool firstTime);
};
