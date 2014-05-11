#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Ouvrir une image : 						display image.png 						==> ouvrir image.png
Information sur l'image : 					identify -ping image.png 					==> infos image.png
PNG en JPEG : 							convert image.png image.jpg 					==> format
Convertir dans un même dossier toutes les images PNG en JPEG :  mogrify -quality 96 -format jpg *.png 				==> touten
Redimensions de l'image : 					convert -adaptative-resize image.png nouvelle_image.png 	==> redimension image.png nouvelle.png
Retourner une image de bas en haut : 				convert -flip image.png image-inversee.png 			==> retroune_HB image.png nouvelle.png
Retourner une image de gauche à droite :		 	convert -flop image.png image-inversee.png
Blur de l'image: 						convert -blur 10x2 img.jpg new_img.jpg 				==> blur image.png
Faire un contour : 						convert -bordercolor #000000 -border image.png new_img.jpg	==> contour image.png
Effet dessin : 							convert -charcoal 4 img.jpg new_img.jpg 			==> dessin image.png
Réglage gamma auto : 						convert -auto-gamma img.jpg new_img.png 			==> gamma_auto image.png
Retourner (vers le bas) : 					convert -flip img.jpg _new_img.jpg 				==> flip image.png
Flou gaussien : 						convert -gaussian-blur 50 img.jpg new_img.jpg 			==> gaussian_blur image.png
Noir et blanc : 						convert -monochrome img.jpg new_img.jpg 			==> n_b image.png
Peinture à l'huile : 						convert -paint 3 img.jpg new_img.jpg 				==> huile image.png
Rotation 90° droite :						convert -rotate "90" img.jpg new_img.png			==> rotation +90 image.png
Rotation -90° gauche:						convert -rotate"-90" img.jpg new_img.pgn			==> rotation -90 image.png
*/

/*Ouverture d'un fichier*/
void ouvrir(char filename[]){
  char commande[50];
  strcat(commande, "display");
  strcat(commande, " ");
  strcat(commande, filename);
  system(commande);
}

/*Donne les informations du fichier*/
void infos(char filename[]){
  char commande[50];
  strcat(commande, "identify");
  strcat(commande, " ");
  strcat(commande, "-ping");
  strcat(commande, " ");
  strcat(commande, filename);
  system(commande);
}

/*Enregistre dans un nouveau format*/
void format(char filename[], char type[]){
  char commande[50];
  strcat(commande, "convert");
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".");
  strcat(commande, type);
  system(commande);
}

/*upside-down*/
void retourne_HB(char filename[]){
  char commande[50];
  strcat(commande, "convert -flip ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".upsidedown.png");
  system(commande);
}

/*effet miroir*/
void retourne_GD(char filename[]){
  char commande[50];
  strcat(commande, "convert -flop ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".mirror.png");
  system(commande);
}

/*blur it all*/
void blur(char filename[]){
  char commande[50];
  strcat(commande, "convert -blur 10x2 ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".blurry.png");
  system(commande);
}

/*dessine un contour*/
void contour(char filename[]){
  char commande[50];
  strcat(commande, "convert -bordercolor #000000 -border ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".border.png");
  system(commande);
}

/*effet dessin*/
void dessin(char filename[]){
  char commande[50];
  strcat(commande, "commande -charcoal 4 ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".dessin.png");
  system(commande);
}

/*noir et blanc*/
void n_b(char filename[]){
  char commande[50];
  strcat(commande, "convert -monochrome ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".black_&_white.png");
  system(commande);
}

/*rotate de i°*/
void rotate(char filename[], char deg[]){
  char commande[50];
  strcat(commande, "convert -rotate \"");
  strcat(commande, deg);
  strcat(commande, "\" ");
  strcat(commande, filename);
  strcat(commande, " ");
  strcat(commande, filename);
  strcat(commande, ".rotate_");
  strcat(commande, deg);
  strcat(commande, "_degrees.png");
  system(commande);
}


int main(int argc, char* argv[]){
  printf("Hello world !\n");
  system("pwd");
  rotate("lena.bmp", "45");

  return 0;
}
