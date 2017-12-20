/*
 * doll.c
 *
 */

#include <stdio.h>
#include <Angel.h>                  //GLUT toolkit
#include <time.h>
#define INIT_VIEW_X 0.0    //Define initial camera position and viewing window values
#define INIT_VIEW_Y 0.0
#define INIT_VIEW_Z -4.5
#define VIEW_LEFT -2.0
#define VIEW_RIGHT 2.0
#define VIEW_BOTTOM -2.0
#define VIEW_TOP 2.0
#define VIEW_NEAR 1.0
#define VIEW_FAR 200.0
GLfloat AmbientLight[]={0.3,0.3,0.3,1.0};                  //Initialization values for lighting
GLfloat DiffuseLight[] ={0.8,0.8,0.8,1.0};
GLfloat SpecularLight[] ={1.0,1.0,1.0,1.0};
GLfloat SpecRef[] = {0.7,0.7,0.7,1.0};
GLfloat LightPos[] = {-50.0,50.0,100.0,1.0};
GLint Shine =128;
GLint walkX=0,zoom=0, walkY=0, lookX=0,lookY=0;
GLint world=1,oldX=-1,oldY=-1;
GLint doll=-1;
GLuint elephant;
float elephantrot;
char ch='1';

void loadObj(char *fname)
{
    FILE *fp;
    int read;
    GLfloat x, y, z;
    char ch;
    elephant=glGenLists(1);
    fp=fopen(fname,"r");
    if (!fp)
    {
        printf("can't open file %s\n", fname);
        exit(1);
    }
    glPointSize(2.0);
    glNewList(elephant, GL_COMPILE);
    {
        glPushMatrix();
        glBegin(GL_POLYGON);
        while(!(feof(fp)))
        {
            read=fscanf(fp,"%c %f %f %f",&ch,&x,&y,&z);
            if(read==4&&ch=='v')
            {
                glVertex3f(x,y,z);
            }
        }
        glEnd();
    }
    glPopMatrix();
    glEndList();
    fclose(fp);
}

void eyeright()
{
    //function for the right eye
    glPushMatrix();
    glTranslatef(.17,1.1,.75);     //Specify the coordinates for the right eye
    glRotatef(-45,0,0,1);
    glScalef(.9,.7,.7);            //Specify the size of the right eye
    glColor3f(1.0,1.0,1.0);       //Specify the color of the eye
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}
void eyeleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.75);     //Specify the position for the left eye
    glRotatef(45,0,0,1);
    glScalef(.9,.7,.7);
    glColor3f(1.0,1.0,1.0);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void legleft()
{
    glPushMatrix();
    glTranslatef(.6,0.05,0);     //Specify the position for the left leg
    glRotatef(-90.0,45,25.0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void legright()
{
    glPushMatrix();
    glTranslatef(-.35,0.008,0.7);     //Specify the position for the right leg
    glRotatef(-140.0,1,0,0);
    glScalef(.8,.8,.8);
    gluCylinder(gluNewQuadric(),.5,.5,.5,30,6);
    glPopMatrix();
}

void armleft()
{
    glPushMatrix();
    glTranslatef(-0.80,1.4,-0.1);     //Specify the position for the left arm
    glRotatef(-90,0,1,0);
    glRotatef(-50,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}
void armright()
{
    glPushMatrix();
    glTranslatef(.77,1.4,.1);      //Specify the position for the right arm
    glRotatef(-90,0,1,0 );
    glRotatef(-130,1,0,0);
    gluCylinder(gluNewQuadric(),.15,.15,.48,30,6);
    glPopMatrix();
}
void handleft()
{
    glPushMatrix();
    glTranslatef(1.12,1.8,.1);     //Specify the position for the left hand
    glRotatef(-90,0,1,0);
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}
void handright()
{
    //glTranslatef itu x,y, z rek!!!!!! parameternya
    glPushMatrix();
    glTranslatef(-1.14,1.8,-0.1);
    glRotatef(-90,0,1,0);    //Specify the position for the right hand
    glScalef(.4,.3,.3);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void mouth()
{
    glPushMatrix();
    glTranslatef(0,.78,.74);
    glScalef(.4,.4,.1);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.4,100,100);
    glPopMatrix();
}

void teeth()
{
    glPushMatrix();
    glColor3f(1.0,1.0,1.0);
    glTranslatef(-.08,.72,.76);
    glTranslatef(.055,0,.005 );
    glutSolidCube(.035);
    glTranslatef(.055,0,0 );
    glutSolidCube(.035);
    glPopMatrix();
}
void eyebrowleft()
{
    glPushMatrix();
    glTranslatef(-.3,1.3,.97);;
    glRotatef(90,0,1,0);
    glRotatef(-20,1,0,0);
    glColor3f(0.0,0.0,0.0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void eyebrowright()
{
    glPushMatrix();
    glTranslatef(.3,1.5,.97);
    glRotatef(270,0,1,0);
    glRotatef(45,1,0,0);
    gluCylinder(gluNewQuadric(),.05,.01,.3,4,6);
    glPopMatrix();
}

void neckring()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(.59,.59,.59);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}


void head()
{
    glPushMatrix();
    glTranslatef(0,1.2,0);
    glScalef(.9 ,.9,.9 );
    glColor3f(1.0,0.5,0.8);
    gluSphere(gluNewQuadric(),1,100,100);
    glPopMatrix();
}

void maintopball()
{
    glPushMatrix();
    glTranslatef(0,2.2,0);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.18,100,100);
    glPopMatrix() ;
}

void hatring()
{
    glPushMatrix();
    glTranslatef(0,1.4,0);
    glScalef(.84,.84,.84);
    glRotatef(90.0,1,0,0);
    glutSolidTorus(.1,1.0,20,20);
    glPopMatrix();
}

void footleft()
{
    glPushMatrix();
    glTranslatef(-.35,0.1,0.7);
    glRotatef(-50.0,45,25.0,0);
    glScalef(1.5,.3,1.5);
    glColor3f(1.0,0.5,0.8);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void footright()
{
    glPushMatrix();
    glTranslatef(.5,0.0,0);
    glRotatef(-37.0,-15,50.0,-70);
    glScalef(1.5,.3,1.5);
    glColor3f(1.0,0.5,0.8);
    gluSphere(gluNewQuadric(),.3,100,100);
    glPopMatrix();
}

void bellyCoatbottom()
{
    glPushMatrix();
    glTranslatef(0,-.2,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluDisk(gluNewQuadric(),0,.8,30,30);
    glPopMatrix();
}

void BellyCoat()
{
    glPushMatrix();
    glTranslatef(0,.5,0);
    glScalef(1,.7,1);
    glRotatef(90.0,1,0,0);
    gluCylinder(gluNewQuadric(),.6,.8,1,100,100);
    glPopMatrix();
}

void pupilleft()
{
    glPushMatrix();
    glTranslatef(-.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void pupilright()
{
    glPushMatrix();
    glTranslatef(.17,1.1,.88);
    glScalef(.9,.9,.9);
    gluSphere(gluNewQuadric(),.1,100,100);
    glPopMatrix();
}

void topbutton()
{
    glPushMatrix();
    glTranslatef(-.1,.4,.85);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void middlebutton()
{
    glPushMatrix()  ;
    glTranslatef(-.1,.15,.98);
    glScalef(1.9,1.9,1.9);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}
void bottombutton()
{
    glPushMatrix();
    glTranslatef(-.1,-.1,.92);
    glScalef(2,2,2);
    glColor3f(0.0,0.0,0.0);
    gluSphere(gluNewQuadric(),.04,100,100);
    glPopMatrix();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//Clear the window
    glColor3ub(255,222,173);
    glPushMatrix();//Save viewing matrix state
    if(world==1)
	{
      glTranslatef(walkX,walkY,zoom);
      glRotatef(lookY,0,1,0);
      glRotatef(lookX,1,0,0);
	}

//	glPushMatrix();
//    glTranslatef(0,0,0);
//    glColor3f(0,0,0);
//    glScalef(2.5,2.5,2.5);
//    glCallList(elephant);
//    glPopMatrix();

    glRotatef(elephantrot,0,1,0);
//    glRotatef(1,elephantrot,1,1);
    elephantrot=elephantrot+0.3;
    if(elephantrot>360)elephantrot=elephantrot-360;

//    *******************Doll***********************
    glPushMatrix();
    glTranslatef(0,-0.6,0);



     if(doll==1)
	{
                  glTranslatef(walkX,walkY,zoom);
                  glRotatef(lookY,0,1,0);
                  glRotatef(lookX,1,0,0);
	}
    eyeright();
    eyeleft();
    eyebrowleft();
    eyebrowright();
//    glColor3f(0.0,1.0,0.0);
//    neckring();
//    glColor3ub(50,40,60);
    legright();
    legleft();
//    glColor3ub(255,90,0);
    armleft();
    armright();
//    BellyCoat();
//    bellyCoatbottom();
    glColor3ub(0,185,0);
    handleft();
    handright();
    mouth();
    teeth();
    glColor3ub(255,222,173);
    head();
    glColor3f(0.0,0.0,0.0);
    footleft();
    footright();
//    topbutton();
//    middlebutton();
//    bottombutton();
    pupilleft();
    pupilright();
    glPopMatrix();

    glPopMatrix();                                     //****Restore matrix state****
    glutSwapBuffers();                             //****Flush drawing commands****
}



void SetupRend()
{
    glClearColor(1,1,1,1);
    glEnable(GL_DEPTH_TEST);         //Enable depth testing
    glEnable(GL_LIGHTING);             //Enable lighting
    glLightfv(GL_LIGHT0,GL_AMBIENT,AmbientLight);//Set up and enable light zero
    glLightfv(GL_LIGHT0,GL_DIFFUSE,DiffuseLight);
    glLightfv(GL_LIGHT0,GL_SPECULAR,SpecularLight);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);                   //Enable color tracking
    glColorMaterial(GL_FRONT,GL_AMBIENT_AND_DIFFUSE);//Set material to follow
    glMaterialfv(GL_FRONT,GL_SPECULAR,SpecRef);//Set specular reflectivity and shine
    glMateriali(GL_FRONT,GL_SHININESS,Shine);
}

void walk(int key,int x,int y)                                      //change positions using arrow keys
{
    if(key==GLUT_KEY_UP)    walkY+=1;
    if(key==GLUT_KEY_DOWN)  walkY-=1;
    if(key==GLUT_KEY_RIGHT) walkX+=1;
    if(key==GLUT_KEY_LEFT)  walkX-=1;
    if(key==GLUT_KEY_PAGE_DOWN)  zoom-=1;
    if(key==GLUT_KEY_PAGE_UP)  zoom+=1;
    if(key==GLUT_KEY_F10)    world=-world;
    if(key==GLUT_KEY_F9)    doll=-doll;

}

void gaze(int x,int y)
{
    if((oldX<0) || (oldY<0))
	{

      oldX=x;
                  oldY=y;
	}
    lookX+=y-oldY;lookY+=x-oldX;oldX=x;oldY=y;
}

void myReshape(int w, int h)
{
    GLfloat Ratio;
    glViewport(0,0,w,h);
    Ratio=1.0*w/h;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0,Ratio,VIEW_NEAR,VIEW_FAR);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(INIT_VIEW_X,INIT_VIEW_Y,INIT_VIEW_Z);
    glLightfv(GL_LIGHT0, GL_POSITION, LightPos);
}

int main(int argc, char ** argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB|GLUT_DEPTH);
    glutInitWindowSize( 512, 512 );
    glutCreateWindow("Kirby");
    glutReshapeFunc(myReshape);
    glutDisplayFunc(Display);
    glutIdleFunc(Display);
    glutSpecialFunc(walk);
    glutPassiveMotionFunc(gaze);
    SetupRend();
    glEnable(GL_NORMALIZE);
//    loadObj("clank.obj");
    glutMainLoop();
}
