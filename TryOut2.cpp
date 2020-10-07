#include <bits/stdc++.h>
#include <iostream>
#include <stdlib.h>
#include<GL/gl.h>
#include <GL/glut.h>
#include<math.h>
#include<cstring>
#include<windows.h>
#include<mmsystem.h>

using namespace std;

float red = 0.0;
float angle = 0.0f;
float _angle1[15] = {270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f, 270.0f};
float hitting_angle[15] = {0.0};
float path[15] = {-0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75, -0.75};
int shot = 0;
bool shot_status[15] = {false};
bool game_over = false;
int level_no = 0;
int time_count[3] = {25, 20, 15};

///Initializes 3D rendering
void initRendering()
{
	glEnable(GL_DEPTH_TEST);
}
///Called when the window is resized
void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w / (double)h, 1.0, 200.0);
}

bool check_overlap (float ang, int shot_no)
{
    for (int i=0; i<15; i++)
    {
        if(shot_status[i] && i != shot_no)
        {
            if (ang < 10.0)
            {
                if (abs(360.0 - hitting_angle[i]) + ang < 10.0)
                {
                    return true;
                }
            }
            else
            {
                if(abs(hitting_angle[i] - ang) < 10.0)
                {
                    printf("%f %f\n", hitting_angle[i], abs(hitting_angle[i] - ang));
                    return true;
                }
            }

            if (hitting_angle[i] > 350)
            {
                if (abs(360.0 - hitting_angle[i]) + ang < 10.0)
                {
                    return true;
                }
            }
        }
    }
}

void reset ()
{
    red = 0.0;
    angle = 0.0f;

    for (int i=0; i<15; i++)
    {
        _angle1[i] = 270.0f;
        hitting_angle[i] = 0.0f;
        path[i] = -0.75f;
        shot_status[i] = false;
    }
    shot = 0;
    level_no = 0;
    time_count[0] = 25;
    time_count[1] = 20;
    time_count[2] = 15;
    glutPostRedisplay();
}

void level_update ()
{
    red = 0.0;
    angle = 0.0f;

    for (int i=0; i<15; i++)
    {
        _angle1[i] = 270.0f;
        hitting_angle[i] = 0.0f;
        path[i] = -0.75f;
        shot_status[i] = false;
    }
    shot = 0;
    level_no++;
    glutPostRedisplay();
}

void render_labels ()
{
    char level[80]  = "Level";
    int len;
    len = strlen(level);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.9, 0.9);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)level[i] );
    }

    char shot_left[80]  = "Shots Left";
    len = strlen(shot_left);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.12, 0.9);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)shot_left[i] );
    }

    int a = 14;
    int i = 0;
    while (i < 14)
    {
        if (shot_status[i] == false)
        {
            a = 14 - i;
            break;
        }
        i++;
    }

    stringstream s;
    s << a << endl;

    string shots = s.str();
    //cout << shots << endl;
    len = shots.length();

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.12, 0.85);

    for(int i=0; i<len-1; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)shots[i] );
    }

    char time_left[80]  = "Time";
    len = strlen(shot_left);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(0.75, 0.9);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)time_left[i] );
    }

    s.str(string());
    s << time_count[level_no] << endl;

    string t = s.str();
    //cout << shots << endl;
    len = t.length();

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(0.75, 0.85);

    for(int i=0; i<len-1; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)t[i] );
    }

    s.str(string());
    s << level_no + 1 << endl;

    string l = s.str();
    //cout << shots << endl;
    len = l.length();

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.9, 0.85);

    for(int i=0; i<len-1; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)l[i] );
    }
}

void game_over_labels ()
{
    char g[80]  = "Game Over!";
    int len;
    len = strlen(g);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.1, 0.9);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)g[i] );
    }

    char p[80]  = "Play Again?";
    len = strlen(p);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.11, 0.8);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)p[i] );
    }

    char y[80]  = "Yes";
    len = strlen(y);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(-0.2, 0.7);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)y[i] );
    }

    char n[80]  = "No";
    len = strlen(n);

    glColor3f(1.0, 1.0, 1.0);

    glRasterPos2f(0.2, 0.7);

    for(int i=0; i<len; i++)
    {
        glutBitmapCharacter( GLUT_BITMAP_9_BY_15, (int)n[i] );
    }
}

void target (void)
{
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslatef(0.0, 0.0, 0.0);
        glRotatef(angle, 0.0, 0.0, 1.0);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/50 ;
            float r=0.15;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y);
            glColor3f(red, 0.0, 0.0);
            if (red < 1.0)
            {
                red += 1.0 / 360.0;
            }
        }
        glEnd();
    glPopMatrix();
}

void projectile (void)
{
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(0.0, -0.75, 0.0);
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/50 ;
            float r=0.03;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y);
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        glTranslatef(0.0, -0.72, 0.0);
        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.0, 0.15);
        glEnd();
    glPopMatrix();
}

void fire(int p)
{
    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        if (path[p] > -0.35)
        {
            glRotatef(_angle1[p], 0.0, 0.0, 1.0);
            glTranslatef(0.33, 0.0, 0.0);
            if (hitting_angle[p] == 0.0)
            {
                //sndPlaySound("fire_bow_sound-mike-koenig.wav",SND_ASYNC);
                hitting_angle[p] = angle;
                if(check_overlap(hitting_angle[p], p))
                {
                    game_over = true;
                    reset();
                }
                if (shot == 14 && level_no != 2)
                {
                    level_update();
                }
            }
        }
        else
        {
            glTranslatef(0.0, path[p] + 0.02, 0.0);
        }
        glBegin(GL_POLYGON);
        for(int i=0;i<200;i++)
        {
            float pi=3.1416;
            float A=(i*2*pi)/50 ;
            float r=0.03;
            float x = r * cos(A);
            float y = r * sin(A);
            glVertex2f(x,y);
        }
        glEnd();
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 1.0, 0.0);
        if (path[p] > -0.35)
        {
            glRotatef(_angle1[p] + 90.0f, 0.0, 0.0, 1.0);
            glTranslatef(0.0, -0.3, 0.0);
        }
        else
        {
            glTranslatef(0.0, path[p] + 0.05, 0.0);
        }
        glBegin(GL_LINES);
            glVertex2f(0.0, 0.0);
            glVertex2f(0.0, 0.15);
        glEnd();
    glPopMatrix();
}

void drawScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity(); ///Reset the drawing perspective
	glMatrixMode(GL_MODELVIEW);

    if (game_over == false)
    {
        render_labels();
        target();

        if (shot < 14)
        {
            projectile();
        }

        int temp = 0;
        while (temp < 15)
        {
            if(shot_status[temp])
            {
                fire(temp);
            }
            temp++;
        }
    }
    else
    {
        game_over_labels();
    }

	glutSwapBuffers();
}

void update(int value)
{
	angle += 2.0f + float(level_no);
	if (angle > 360)
    {
		angle -= 360;
	}

	int temp = 0;

	while (temp < 15)
    {
        if (path[temp] > -0.35 && shot_status[temp])
        {
            _angle1[temp] += 2.0f + float(level_no);
            if (_angle1[temp] > 360)
            {
                _angle1[temp] -= 360;
            }
        }
        temp++;
    }

    temp = 0;

	while (temp < 15)
    {
        if (path[temp] < -0.35 && shot_status[temp])
        {
            path[temp] += 0.01;
        }
        temp++;
    }

	glutPostRedisplay(); ///Tell GLUT that the display has changed

	///Tell GLUT to call update again in 25 milliseconds
	glutTimerFunc(25, update, 0);
}

void update_time(int x)
{
    if (time_count[level_no] == 0)
    {
        game_over = true;
        game_over_labels();
    }
    else
    {
        time_count[level_no]--;
    }
    glutTimerFunc(1000, update_time, 0);
}

void mouse(int button, int state, int x, int y)
{
   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && game_over == false)
   {
       printf("%d %d %d\n", shot, x, y);
       fire(shot);
       shot_status[shot] = true;
       //sndPlaySound("Bow_Fire_Arrow-Stephan_Schutze-2133929391.wav",SND_ASYNC);
       if (shot < 14)
       {
           shot++;
       }
   }

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 315 && x <= 350 && y >= 105 && y <= 120 && game_over == true)
   {
       //printf("%d %d\n", x, y);
       game_over = false;
       reset();
   }

   if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN && x >= 480 && x <= 505 && y >= 105 && y <= 120 && game_over == true)
   {
       exit(EXIT_SUCCESS);
   }
}

int main(int argc, char** argv)
{
	///Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);

	///Create the window
	glutCreateWindow("Game");
	initRendering();

	///Set handler functions
	glutDisplayFunc(drawScene);
	glutReshapeFunc(handleResize);

	glutTimerFunc(25, update, 0);
	glutTimerFunc(1000, update_time, 0);
	glutMouseFunc(mouse);

	glutMainLoop();
	return 0;
}

