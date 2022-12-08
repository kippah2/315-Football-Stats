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

//the main menu that leads to the next menus

void stats_menu()
{
	printf("*********************************************");
	printf("\n*    The C Team Football Stats Program    *");
	printf("\n*  Please Choose From the Options Below   *");
	printf("\n*           1. Offensive Stats            *");
	printf("\n*           2. Defensive Stats            *");
	printf("\n*           3. Win statistics             *");
	printf("\n*******************************************\n");
}

//display this menu if the choice is 1

void offensive_menu()
{
	printf("*******************************************");
	printf("\n* Choose Which Stat You Want to Look at *");
	printf("\n*          1. Total Receives made   (total yards passing)    *");
	printf("\n*          2. Total Receving Touchdowns *");
	printf("\n*          3. Total Yards Travelled     *");
	printf("\n*          4. Total Yards Rushing       *");
	printf("\n*          5. Total Rushed Touchdowns   *");
	printf("\n*          6. Total Yards Passing       *");
	printf("\n*          7. Total Completed Passes    *");
	printf("\n*          8. Total Passed Touchdowns   *");
	printf("\n*****************************************\n");

}

//display this menu if the choice is 2

void defensive_menu()
{
	printf("*******************************************");
	printf("\n*          1. Total Receives made       *");
	printf("\n*          2. Total Receving Touchdowns *");
	printf("\n*          3. Total Yards Travelled     *");
	printf("\n*          4. Total Rushing Yards       *");
	printf("\n*          5. Total Rushing Touchdowns  *");
	printf("\n*          6. Total Yards Passed        *");
	printf("\n*          7. Total Completed Passes    *");
	printf("\n*          8. Total Passed Touchdowns   *");
	printf("\n*****************************************\n");

}
//display this menu if choice is 3

void win_menu()
{
	printf("*******************************************");
	printf("\n*          1. Total Wins this season    *");
	printf("\n*          2. Total Loses this season   *");
	printf("\n*          3. Win Percentage this season*");
	printf("\n*****************************************\n");

}
//display this menu when the user selects a choice from either the offensive or defensive menu

void specifics()
{
	printf("*******************************************");
	printf("\n*   Please Specify Which Team and Year  *");
	printf("\n*******************************************");

	printf("\n*   Enter the Team you Wish to Display  *");
	// possibly display a table or list of teams?
	//scanf("%s", &team);
	printf("\n*   Enter the Year you Wish to Display  *");
//	scanf("%s", &year);
}
//after the specifics are entered the stats for that team and year depending
//on what the user selected will be shown to them

//just a draft. can be changed however to fit the project and make it as easy as possible

//just a draft. can be changed however to fit the project and make it as easy as possible
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
 
 


//printf("%s\n", mem->memory);
  return realsize;
}



// function to handle the response data from the API
size_t write_response_data_offensive(void *ptr, size_t size, size_t nmemb, void *stream) {
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
    }
    char* user_input_name;
    
    
    printf("Input a team name to find their stats: ");
    scanf("%s", user_input_name);
    printf("Team Name: %s\n", user_input_name);

int l_length;
l_length=(30-strlen(user_input_name));

//must have function before each parse    
 memcpy(data, ptr, data_size);
// parse the response data and extract the relevant information
  data[data_size] = '\0';   
    char* team_receives = strstr(data, user_input_name);
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
    team_touchdowns += strlen("touchdowns:") + 6; //27
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
    team_touchdowns += strlen("yards:") + 6;//5
    char* end = strchr(team_touchdowns, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Yards travelled:%s\n", team_touchdowns);}
    
    
    
    
  }
  
//-----------------------------------------------------------------------------------------------------------------------------------------------------------
size_t write_response_data_defensive(void *ptr, size_t size, size_t nmemb, void *stream) {
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
    }
    char* user_input_name;
    
    
    printf("Input a team name to find their stats: ");
    scanf("%s", user_input_name);
    printf("Team Name: %s\n", user_input_name);

int l_length;
l_length=(30-strlen(user_input_name));




//must have function before each parse    
 memcpy(data, ptr, data_size);
// parse the response data and extract the relevant information
  data[data_size] = '\0';   
    char* team_receives = strstr(data, user_input_name);
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
    team_touchdowns += strlen("touchdowns:") + 6; //27
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
    team_touchdowns += strlen("yards:") + 6;//5
    char* end = strchr(team_touchdowns, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Yards travelled:%s\n", team_touchdowns);}
    
    
    
    
  }


//-----------------------------------------------------------------------------------------------------------------------------------------------------------
size_t write_response_data_win(void *ptr2, size_t size, size_t nmemb, void *stream) {
  


  // calculate the size of the response data
  size_t data_size = size * nmemb;

  // allocate memory for the response data
  char* data = malloc(data_size + 1);
  if (data == NULL) {
    return 0;
  }

  // copy the response data from the API to the allocated memory
  memcpy(data, ptr2, data_size);
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
    }
    char* user_input_name;
    
    //call win menu
 /* int win_menu_option;
  printf("Which option would you like:  ");
  scanf("%d", &win_menu_option);*/
  
  //have user input team name
    printf("Input a team name to find their stats: ");
    scanf("%s", user_input_name);
    printf("Team Name: %s\n", user_input_name);

int l_length;
l_length=(30-strlen(user_input_name));


//must have function before each parse    
 memcpy(data, ptr2, data_size);
 data[data_size] = '\0';   
 
 // parse the response data and extract the relevant information
    char* team_wins = strstr(data, user_input_name);
    if (team_wins != NULL) {
    team_wins += strlen("wins:") + (33-l_length); //11
    char* end = strchr(team_wins, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Wins this season%s\n", team_wins);
    }
 
v_data = team_wins;
    
  memcpy(data, ptr2, data_size);
  data[data_size] = '\0';   
    char* team_loses = strstr(data, v_data);
  if (team_loses != NULL) {
    team_loses += strlen("losses:") + 4; //27
    char* end = strchr(team_loses, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Losses this season%s\n", team_loses);
    }
    
v_data=team_loses;

   memcpy(data, ptr2, data_size);
  data[data_size] = '\0';   
    char* team_percent = strstr(data, v_data);
  if (team_percent != NULL) {
    team_percent += strlen("winRatePercentage:") + 6;//5
    char* end = strchr(team_percent, ',');
    if (end != NULL) {
      *end = '\0';
    }
    printf("Win Rate Percentage:%s\n", team_percent);
    }
    
    
   
    
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
  int user_main_menu_input;
  int user_main_menu_input2;
  scanf("%d", &user_main_menu_input);
  
  char* nfl_stats;
  char* position_stats;
  int year_url = 2019;
  if (curl)
    {
      //define api call as GET and direct it to given URL
      curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "GET");
      if (user_main_menu_input==1){
      		nfl_stats ="offense";
      		offensive_menu();
      		scanf("%d", &user_main_menu_input2);
      
      if (user_main_menu_input2==1){
      		position_stats ="rushing-stats";
      }
      else{
      		position_stats ="receiving-stats";
            }
      }
      if (user_main_menu_input==2){
      		nfl_stats ="defense";
      		defensive_menu();
      		scanf("%d", &user_main_menu_input2);
      
      if (user_main_menu_input2==1){
      		position_stats ="rushing-stats";
      }
      else{
      		position_stats ="receiving-stats";
            }
            }
      else{
      		nfl_stats ="win-stat";
      		win_menu();
            }
      
      
      
      
      
      curl_easy_setopt (curl, CURLOPT_CUSTOMREQUEST, "GET");
      char* nfl_url;
      nfl_url =("https://nfl-team-stats.p.rapidapi.com/v1/nfl-stats/teams/win-stats/2019");
      //printf("%s", nfl_url);
      curl_easy_setopt (curl, CURLOPT_URL, nfl_url);
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
//send data to struct MemoryStruct
      switch(user_main_menu_input){
      case  1:
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_response_data_offensive_receiving);
      break;
      case  2:
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_response_data_defensive_receiving);
      break;
      case 3:
      curl_easy_setopt (curl, CURLOPT_WRITEFUNCTION, write_response_data_win);
      break;
      default:
      	printf("Input not recognized");
      	}
      
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





//after the specifics are entered the stats for that team and year depending
//on what the user selected will be shown to them

//just a draft. can be changed however to fit the project and make it as easy as possible
int main ()
{
  int loop_menu = 1;
  while (loop_menu!=0){
  stats_menu();
  request();
  }
  
  
  
  
  
  
}
