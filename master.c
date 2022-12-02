//Project by Jeffrey Samuels, Ryan Flanagan, Shawn Swathwood, Jordan Jollief, and Charlie Estes
//Make sure you've installed libcurl. This is most easily done on Linux using 'sudo apt-get install libcurl4-openssl-dev'.
//When you compile it, use 'gcc master.c -lcurl'.


//TO DO: Implement JSON parser. Use data structures to handle parsed data. Create ASCII table to display information to user. Create interactive menu for user to input what stats, year, and team they want to look at.

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <curl/curl.h>
#include <curl/easy.h>
//For parsing, we're going to want to use Jannson. See 'https://github.com/akheron/jansson' and 'https://jansson.readthedocs.io/en/latest/'


//This function handles the API call. We will modify this later so that it can call a specific API endnode. We do this by changing the URL. We can implement this by giving the user an interactive menu.
//API being used is NFL Team Stats. 'https://rapidapi.com/DathanStoneDev/api/nfl-team-stats'
static char *request() {
	CURL *curl = NULL;
	CURLcode res;
	curl = curl_easy_init();
	if(curl) {
	  curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
	  curl_easy_setopt(curl, CURLOPT_URL, "https://nfl-team-stats.p.rapidapi.com/v1/nfl-stats/teams/receiving-stats/offense/2019");
	  curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
	  curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
	  struct curl_slist *headers = NULL;
	  headers = curl_slist_append(headers, "x-rapidapi-key: f214693c05mshcb4f9b9797a4754p1c6cc7jsn454debc36d9a");
	  headers = curl_slist_append(headers, "x-rapidapi-host: nfl-team-stats.p.rapidapi.com");
	  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
	  res = curl_easy_perform(curl);
	}
	curl_easy_cleanup(curl);
}

//We need an interactive menu where the user is able to choose what kinds of stats they want.
//Different API endpoint URLs are broken up by defense/offense and for the given year.
//If we want them to have the option to choose more filtering options, like which team they want to see the stats for, we're going to need to implement that manually with the parser.

//We need a way of passing the results of the request function to the Jannson parser

//Then we need to make to make the parser segregate information by team stats

//We need to then have data structures for handling each group of information to pass to the display stats function.


int main() {
	request();
}
