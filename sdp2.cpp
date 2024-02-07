#include <gtk/gtk.h>
#include <iostream>

using namespace std;

struct struct_
{
  int meorizeArray[10];
};

struct struct_ memorize_struct[9][9];
int input_from_file[9][9];
string get_i_j[100];
int error_flag = 3;
int Game_Over_flag = 0;

// point last widget, when user clicked the any grid of 9*9 grid
int ii = -1;
int jj = -1;
int Flag_ = 0;
string check_widget_label;

GtkWidget *Main_window, *vartical_box, *label2, *label3_for_show_masg;
GtkWidget *window, *button1, *button2, *Fixed_box, *Fixed_box2, *sudoko_widget;
GtkWidget *image, *label, *back_button, *number_button[9], *Fixed_box3;
GtkWidget *level[5], *separator, *sudoko_box_widget[9][9], *Erase_button, *Write; 

void activate();

static void back_function(GtkWidget *widget, gpointer value)
{
  cout << "Back Button Clicked Successfully\n";
  gtk_container_remove(GTK_CONTAINER(Main_window), Fixed_box2);
  activate();
}

static void back_function2(GtkWidget *widget, gpointer value)
{
  cout << "Back Button Clicked Successfully\n";
  gtk_container_remove(GTK_CONTAINER(Main_window), Fixed_box3);
  activate();
}

void myCSS_for_colour()
{
  GtkCssProvider *provider;
  GdkDisplay *display;
  GdkScreen *screen;

  provider = gtk_css_provider_new();
  display = gdk_display_get_default();
  screen = gdk_display_get_default_screen(display);
  gtk_style_context_add_provider_for_screen(screen, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

  const gchar *myCssFile = "style.css";
  GError *error = 0;

  gtk_css_provider_load_from_file(provider, g_file_new_for_path(myCssFile), &error);
  g_object_unref(provider);
}

void print_array()
{
  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
      cout << input_from_file[i][j] << " ";
    cout << endl;
  }
}

bool check_value_is_right(int i, int j, int value)
{
  if (memorize_struct[i][j].meorizeArray[value])
    return false;

  for (int k = 0; k < 9; k++)
  {
    if (input_from_file[i][k] == value)
    {
      memorize_struct[i][k].meorizeArray[value]++;
      return false;
    }
  }
  for (int k = 0; k < 9; k++)
  {
    if (input_from_file[k][j] == value)
    {
      memorize_struct[k][j].meorizeArray[value]++;
      return false;
    }
  }

  int new_i, new_j;

  if ((i + 1) % 3 == 0 && i != 0)
    new_i = i - 2;
  else if ((i + 1) % 3 == 2)
    new_i = i - 1;
  else
    new_i = i;

  if ((j + 1) % 3 == 0 && j != 0)
    new_j = j - 2;
  else if ((j + 1) % 3 == 2)
    new_j = j - 1;
  else
    new_j = j;

  int lenth_of_i = new_i + 2;
  int lenth_of_j = new_j + 2;

  for (int k = new_i; k <= lenth_of_i; k++)
  {
    for (int l = new_j; l <= lenth_of_j; l++)
    {
      if (k == i && l == j)
        continue;

      if (input_from_file[k][l] == value)
      {
        memorize_struct[k][j].meorizeArray[value]++;
        return false;
      }
    }
  }
  return true;
}

static void set_value_function(GtkWidget *widget, gpointer value)
{
  int got_i = ii;
  int got_j = jj;
  int user_input_value = stoi(gtk_button_get_label(GTK_BUTTON(widget)));

  cout<< Flag_ << "\n";

  if (got_i >= 0 && got_j >= 0 && Flag_ == 0){
    if (check_value_is_right(got_i, got_j, user_input_value))
    {
      gtk_label_set_label(GTK_LABEL(label3_for_show_masg), "GREAT JOB!!   YOU  CAN  DO  IT.");

      input_from_file[got_i][got_j] = user_input_value;
      cout << "Value : " << user_input_value << " is set sucsess\n\n";

      gtk_button_set_label(GTK_BUTTON(sudoko_box_widget[got_i][got_j]), gtk_button_get_label(GTK_BUTTON(widget)));
    }
    else
    {
      cout << "Error Msg printed successfully..\n";
      gtk_label_set_label(GTK_LABEL(label3_for_show_masg), "OOPS!!  WRONG,  PLEASE  TRY  AGAIN");
    }
  }
}

static void Erase_Button_activate_function(GtkWidget *W, gpointer V)
{
  cout<<"Erase Button Activate\n";
  gtk_label_set_label(GTK_LABEL(label3_for_show_masg), "ERASE  BUTTON  ACTIVATE!");
  Flag_ = 1;
  int X ;//= stoi(check_widget_label);

  if(Flag_ == 1){
    input_from_file[ii][jj] = 0;
    memorize_struct[ii][jj].meorizeArray[X] == 0;
    gtk_button_set_label(GTK_BUTTON(sudoko_box_widget[ii][jj]), " ");
  }
}

static void Write_Button_acticate_function(GtkWidget *W, gpointer V)
{
  cout<<"Write Button Activate\n";
  gtk_label_set_label(GTK_LABEL(label3_for_show_masg), "WRITE  BUTTON  ACTIVATE!");
  Flag_ = 0;
}

char msge[27] = {"YOUR  LOCATION  INDEX  "} ;

static void check_data_from_player(GtkWidget *wiet, gpointer value)
{
  check_widget_label = gtk_button_get_label(GTK_BUTTON(wiet));
  ii = stoi(gtk_button_get_label(GTK_BUTTON(value)));
  jj = stoi(gtk_widget_get_name(GTK_WIDGET(value)));

  msge[25] = ii + '0';
  msge[24] = ',';
  msge[23] = jj + '0';
  msge[26] = '.';

  gtk_label_set_label(GTK_LABEL(label3_for_show_masg), msge);

  cout << "ii: " << ii << " jj: " << jj << endl;

  cout << check_widget_label << endl;
}

void play_game_page()
{
  cout << "Play_gmae_function open successfully\n";
  gtk_container_remove(GTK_CONTAINER(Main_window), Fixed_box2);

  Fixed_box3 = gtk_fixed_new();
  back_button = gtk_button_new_with_label("Back");
  Erase_button = gtk_button_new_with_label("Erase");
  Write = gtk_button_new_with_label("Write");
  label3_for_show_masg = gtk_label_new("Hey!! I Will provide all updates to you here...");

  gtk_fixed_put(GTK_FIXED(Fixed_box3), label3_for_show_masg, 250, 390);
  gtk_fixed_put(GTK_FIXED(Fixed_box3), back_button, 10, 10);
  gtk_fixed_put(GTK_FIXED(Fixed_box3), Erase_button, 20, 390);
  gtk_fixed_put(GTK_FIXED(Fixed_box3), Write, 20, 355);


  g_signal_connect(Erase_button, "clicked", G_CALLBACK(Erase_Button_activate_function), nullptr);
  g_signal_connect(Write, "clicked", G_CALLBACK(Write_Button_acticate_function), nullptr);

  for (int i = 1; i <= 9; i++)
  {
    char s[2];
    sprintf(s, "%d", i);
    number_button[i - 1] = gtk_button_new_with_label(s);

    g_signal_connect(number_button[i - 1], "clicked", G_CALLBACK(set_value_function), nullptr);

    gtk_fixed_put(GTK_FIXED(Fixed_box3), number_button[i - 1], 80 + (i * 50), 450);
  }

  for (int i = 0; i < 9; i++)
  {
    int x = 130 + i * 50;
    for (int j = 0; j < 9; j++)
    {
      int y = 37 + j * 34;
      if (input_from_file[i][j] != 0)
      {
        char s[2];
        sprintf(s, "%d", input_from_file[i][j]);
        sudoko_box_widget[i][j] = gtk_button_new_with_label(s);
        gtk_fixed_put(GTK_FIXED(Fixed_box3), sudoko_box_widget[i][j], x, y);
      }
      else
      {
        sudoko_box_widget[i][j] = gtk_button_new_with_label(" ");
        gtk_fixed_put(GTK_FIXED(Fixed_box3), sudoko_box_widget[i][j], x, y);
      }
    }
  }
  gtk_container_add(GTK_CONTAINER(Main_window), Fixed_box3);

  int pointer_flag = 0;

  for (int i = 0; i < 9; i++)
  {
    for (int j = 0; j < 9; j++)
    {
      string s = get_i_j[pointer_flag];
      int a = s[0] - '0';
      int b = s[1] - '0';
      if (a == i && b == j)
      {
        pointer_flag++;
        continue;
      }
      GtkWidget *Position;
      char findPosition_i[2];
      sprintf(findPosition_i, "%d", i);
      char findPosition_j[2];
      sprintf(findPosition_j, "%d", j);
      Position = gtk_button_new_with_label(findPosition_i);
      gtk_widget_set_name(GTK_WIDGET(Position), findPosition_j);
      g_signal_connect(sudoko_box_widget[i][j], "clicked", G_CALLBACK(check_data_from_player), Position);
    }
  }

  g_signal_connect(back_button, "clicked", G_CALLBACK(back_function2), NULL);

  gtk_widget_show_all(Main_window);
}

static void level_function(GtkWidget *widget, gpointer value)
{
  cout << "Level Button Clicked Successfully\n";
  string level_name = gtk_button_get_label(GTK_BUTTON(value));
  cout << level_name << endl;

  if (level_name[6] == '1')
  {
    int num = 0;
    int string_flag = 0;
    FILE *file;
    file = fopen("file1.txt", "r");
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
      {
        fscanf(file, "%d", &num);
        if (num != 0)
        {
          get_i_j[string_flag] = to_string(i);
          get_i_j[string_flag] = get_i_j[string_flag] + to_string(j);
          string_flag++;
        }
        input_from_file[i][j] = num;
      }
    fclose(file);
  }
  else if (level_name[6] == '2')
  {
    int num = 0;
    int string_flag = 0;
    FILE *file;
    file = fopen("file2.txt", "r");
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
      {
        fscanf(file, "%d", &num);
        if (num != 0)
        {
          get_i_j[string_flag] = to_string(i);
          get_i_j[string_flag] = get_i_j[string_flag] + to_string(j);
          string_flag++;
        }
        input_from_file[i][j] = num;
      }
    fclose(file);
  }
  else if (level_name[6] == '3')
  {
    int num = 0;
    int string_flag = 0;
    FILE *file;
    file = fopen("file3.txt", "r");
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
      {
        fscanf(file, "%d", &num);
        if (num != 0)
        {
          get_i_j[string_flag] = to_string(i);
          get_i_j[string_flag] = get_i_j[string_flag] + to_string(j);
          string_flag++;
        }
        input_from_file[i][j] = num;
      }
    fclose(file);
  }
  else if (level_name[6] == '4')
  {
    int num = 0;
    int string_flag = 0;
    FILE *file;
    file = fopen("file4.txt", "r");
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
      {
        fscanf(file, "%d", &num);
        if (num != 0)
        {
          get_i_j[string_flag] = to_string(i);
          get_i_j[string_flag] = get_i_j[string_flag] + to_string(j);
          string_flag++;
        }
        input_from_file[i][j] = num;
      }
    fclose(file);
  }
  else if (level_name[6] == '5')
  {
    int num = 0;
    int string_flag = 0;
    FILE *file;
    file = fopen("file5.txt", "r");
    for (int i = 0; i < 9; i++)
      for (int j = 0; j < 9; j++)
      {
        fscanf(file, "%d", &num);
        if (num != 0)
        {
          get_i_j[string_flag] = to_string(i);
          get_i_j[string_flag] = get_i_j[string_flag] + to_string(j);
          string_flag++;
        }
        input_from_file[i][j] = num;
      }
    fclose(file);
  }

  print_array();

  play_game_page();
}

static void start_game_function(GtkWidget *widget, gpointer value)
{
  cout << "Start Game Button Clicked Successfully\n";
  gtk_container_remove(GTK_CONTAINER(Main_window), Fixed_box);

  Fixed_box2 = gtk_fixed_new();
  label2 = gtk_label_new("GAME LEVEL");
  back_button = gtk_button_new_with_label("Back");

  gtk_fixed_put(GTK_FIXED(Fixed_box2), back_button, 10, 10);
  gtk_fixed_put(GTK_FIXED(Fixed_box2), label2, 290, 120);

  for (int i = 1; i <= 5; i++)
  {
    char s[2];
    sprintf(s, "%d", i);
    char level_word[8] = {"Level-"};
    strcat(level_word, s);
    level[i - 1] = gtk_button_new_with_label(level_word);

    gtk_fixed_put(GTK_FIXED(Fixed_box2), level[i - 1], 290, 100 + (i * 50));
  }

  gtk_container_add(GTK_CONTAINER(Main_window), Fixed_box2);

  g_signal_connect(back_button, "clicked", G_CALLBACK(back_function), NULL);
  g_signal_connect(level[0], "clicked", G_CALLBACK(level_function), level[0]);
  g_signal_connect(level[1], "clicked", G_CALLBACK(level_function), level[1]);
  g_signal_connect(level[2], "clicked", G_CALLBACK(level_function), level[2]);
  g_signal_connect(level[3], "clicked", G_CALLBACK(level_function), level[3]);
  g_signal_connect(level[4], "clicked", G_CALLBACK(level_function), level[4]);

  gtk_widget_show_all(Main_window);
}

void activate()
{
  cout << "Activate Function\n";

  Fixed_box = gtk_fixed_new();
  button1 = gtk_button_new_with_label(" Start Game ");
  button2 = gtk_button_new_with_label("    Quit    ");
  image = gtk_image_new_from_file("sudoko_pic.png");
  label = gtk_label_new("Classic Sudoko");

  gtk_fixed_put(GTK_FIXED(Fixed_box), label, 300, 270);
  gtk_fixed_put(GTK_FIXED(Fixed_box), image, 240, 20);
  gtk_fixed_put(GTK_FIXED(Fixed_box), button1, 295, 380);
  gtk_fixed_put(GTK_FIXED(Fixed_box), button2, 310, 430);

  gtk_container_add(GTK_CONTAINER(Main_window), Fixed_box);

  g_signal_connect(button2, "clicked", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(button1, "clicked", G_CALLBACK(start_game_function), NULL);

  gtk_widget_show_all(Main_window);
}

int main(int argc, char **argv)
{
  gtk_init(&argc, &argv); // initialize the GTK........
  myCSS_for_colour();
  // code start here...................

  Main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(Main_window, "delete-event", G_CALLBACK(gtk_main_quit),
                   NULL);
  gtk_window_set_default_size(GTK_WINDOW(Main_window), 700, 500);

  gtk_window_set_position(GTK_WINDOW(Main_window), GTK_WIN_POS_NONE);

  gtk_window_set_title(GTK_WINDOW(Main_window), "Sudoko 2023");

  gtk_window_set_resizable(GTK_WINDOW(Main_window), false);

  activate();

  gtk_widget_show_all(Main_window);
  gtk_main();

  return 0;
}
