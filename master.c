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

  //printf("%s", mem->memory);

  return realsize;
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
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
      curl_easy_setopt (curl, CURLOPT_WRITEDATA, (void *) &chunk);

      //now that parameters for curl are set, run curl
      res = curl_easy_perform (curl);

      //if curl function doesnt return success, say there was an error
      if (res != CURLE_OK)
	{
	  fprintf (stderr, "curl_easy_perform() failed: %s\n",
		   curl_easy_strerror (res));
	}
      else
	{
	  printf ("%lu bytes retrieved\n", (unsigned long) chunk.size);
	}
    }
  //cleans up curl from memory
  curl_easy_cleanup (curl);
  free (chunk.memory);

  curl_global_cleanup ();

}

//We need an interactive menu where the user is able to choose what kinds of stats they want.
//Different API endpoint URLs are broken up by defense/offense and for the given year.
//If we want them to have the option to choose more filtering options, like which team they want to see the stats for, we're going to need to implement that manually with the parser.

//We need a way of passing the results of the request function to the Jannson parser

//Then we need to make to make the parser segregate information by team stats

//We need to then have data structures for handling each group of information to pass to the display stats function.


int main ()
{
  request ();
}
