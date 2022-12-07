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


//We will probably need another, smaller structure that holds different statistics about a team. This will need to be done post-parsing.

//Defines structure for holding the results of the API call. Build another function that uses what happens in here to parse it.
struct MemoryStruct
{
  char *memory;
  size_t size;
};

//This function stores the results from the API call into struct mem of type MemoryStruct

/*
static size_t
WriteMemoryCallback (void *contents, size_t size, size_t nmemb, void *userp)
{

  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *) userp;

  char *ptr = realloc (mem->memory, mem->size + realsize + 1);
  if (!ptr)
    {
      printf ("not enough memory (realloc returned NULL)\n");
      return 0;
    }

  mem->memory = ptr;
  memcpy (&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
 


//printf("%s\n", mem->memory);
  return realsize;
}


*/
// function to handle the response data from the API
size_t write_response_data(void *ptr, size_t size, size_t nmemb, void *stream) {
  // calculate the size of the response data
  size_t data_size = size * nmemb;

  // allocate memory for the response data
  char* data = malloc(data_size + 1);
  if (data == NULL) {
    return 0;
  }

  // copy the response data from the API to the allocated memory
  memcpy(data, ptr, data_size);
  data[data_size] = '\0';

 char *v_data;
// parse the response data and extract the relevant information
  char* team_name = strstr(data, "name");
  if (team_name != NULL) {
    team_name += strlen("name") + 3;
    char* end = strchr(team_name, '"');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Team Name: %s\n", team_name);}

int l_length;
l_length=(30-strlen("chargers"));

//must have function before each parse    
 memcpy(data, ptr, data_size);
// parse the response data and extract the relevant information
  data[data_size] = '\0';   
    char* team_receives = strstr(data, "Chargers");
  if (team_receives != NULL) {
    team_receives += strlen("receives:") + (33-l_length); //11
    char* end = strchr(team_receives, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Receives made%s\n", team_receives);}
 
v_data = team_receives;
    
  memcpy(data, ptr, data_size);
  data[data_size] = '\0';   
    char* team_touchdowns = strstr(data, v_data);
  if (team_touchdowns != NULL) {
    team_touchdowns += strlen("touchdowns:") + (30-l_length); //27
    char* end = strchr(team_touchdowns, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Touchdowns made%s\n", team_touchdowns);}
    
v_data=team_touchdowns;
   memcpy(data, ptr, data_size);
  data[data_size] = '\0';   
    char* team_yards = strstr(data, v_data);
  if (team_touchdowns != NULL) {
    team_touchdowns += strlen("yards:") + (30-l_length);//5
    char* end = strchr(team_touchdowns, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Yards travelled:%s\n", team_touchdowns);}
    
    
    
    
  }


//This function handles the API call. We will modify this later so that it can call a specific API endnode. We do this by changing the URL. We can implement this by giving the user an interactive menu.
//API being used is NFL Team Stats. 'https://rapidapi.com/DathanStoneDev/api/nfl-team-stats'

static char *
request ()
{

  struct MemoryStruct chunk;
  chunk.memory = malloc (1);
  chunk.size = 0;

  CURL *curl;
  CURLcode res;
  curl = curl_easy_init ();
  if (curl)
    {
      //define api call as GET and direct it to given URL
      curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "GET");
      curl_easy_setopt (curl, CURLOPT_URL,
			"https://nfl-team-stats.p.rapidapi.com/v1/nfl-stats/teams/receiving-stats/offense/2019");
      curl_easy_setopt (curl, CURLOPT_FOLLOWLOCATION, 1L);

      //use curl over https
      curl_easy_setopt (curl, CURLOPT_DEFAULT_PROTOCOL, "https");

      struct curl_slist *headers = NULL;

      //send api key in curl header to endnode can identify who is requesting
      headers =
	curl_slist_append (headers,
			   "x-rapidapi-key: f214693c05mshcb4f9b9797a4754p1c6cc7jsn454debc36d9a");
      //define API host in header of curl
      headers =
	curl_slist_append (headers,
			   "x-rapidapi-host: nfl-team-stats.p.rapidapi.com");

      curl_easy_setopt (curl, CURLOPT_HTTPHEADER, headers);

      //send data to struct MemoryStruct
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_response_data);
     // curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) &chunk);

      //now that parameters for curl are set, run curl
      res = curl_easy_perform (curl);

      //if curl function doesnt return success, say there was an error
 /*     if (res != CURLE_OK)
	{
	  fprintf (stderr, "curl_easy_perform() failed: %s\n",
		   curl_easy_strerror (res));
	}
      else
	{
	  printf ("%lu bytes retrieved\n", (unsigned long) chunk.size);
	}
	
*/
    }
  //cleans up curl from memory
  curl_easy_cleanup (curl);
  free (chunk.memory);

  curl_global_cleanup();

}

//We need an interactive menu where the user is able to choose what kinds of stats they want.
//Different API endpoint URLs are broken up by defense/offense and for the given year.
//If we want them to have the option to choose more filtering options, like which team they want to see the stats for, we're going to need to implement that manually with the parser.

//We need a way of passing the results of the request function to the Jannson parser

//Then we need to make to make the parser segregate information by team stats

//We need to then have data structures for handling each group of information to pass to the display stats function.





int main ()
{
  request();
  
}

