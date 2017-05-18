#include <GL/gl.h> // fichier d'inclusion de la librairie OpenGL
#include <GL/glut.h> // fichier d'inclusion de la librairie GLUT


// Fonction appellée au début
void InitGL()
{
    glEnable(GL_DEPTH_TEST);
}

// Fonction qui redessine la scene
void DrawGLScene(void)
{
   // C'est ici qu'on va dessiner
 
   // On précise à OpenGL la couleur utilisée pour effacer l'écran
   // R, G, B, A
   glClearColor(0, 0, 0, 0);


   // On efface l'écran et le ZBuffer
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


   // On initialise les transformations
   glLoadIdentity();

   // On peut dessiner ici

   // On affiche ce qu'on vient de rendre
   glutSwapBuffers();
   glutReportErrors();
}

// Cette fonction est appellée quand la fenêtre est redimensionnée
void ResizeGLScene(int w, int h)
{
   // On règle les paramètres de projection
   glViewport(0,0,w,h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   gluPerspective(45.0f,(GLfloat)w/(GLfloat)h,0.1f,100.0f);
   glMatrixMode(GL_MODELVIEW);
}

// Fonction appellée par GLUT quand il n'y a rien a faire
void Idle()
{
   // On demande à glut d'afficher à nouveau l'image
   glutPostRedisplay();
}


// Le main
int main(int argc, char ** argv)
{
   // On initialise glut
   glutInit(&argc, argv);

   // On initialise les surfaces en RGBA (Red, Green, Blue, Alpha) en activant
   // le double buffering et le depth buffer
   glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
   
   // On précise la taille de la fenetre
   glutInitWindowSize (800, 600);

   // On créé la fenêtre
   glutCreateWindow ("Mon premier programme");
   
   // On initialise diverse chose
   InitGL();

   // On donne à glut la fonction de rendu
   glutDisplayFunc(DrawGLScene);

   // On donne à glut la fonction d'idle
   glutIdleFunc(Idle);

   // On donne à glut la fonction de redimensionnement
   glutReshapeFunc(ResizeGLScene);
   
   // Et on démarre !
   glutMainLoop();
   
   return 0;
}
