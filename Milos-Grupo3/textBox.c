#include "textBox.h"


textBox dialogueLoad() {
	textBox dialogue;
	
	dialogue.x = 0;
	dialogue.y = 500;
	dialogue.width = SCREEN_WIDTH;
	dialogue.height = 100;
	
	dialogue.boxColor = BUTTON_COLOR_NORMAL;
	return dialogue;
}


void drawDialogue(textBox * text, ALLEGRO_FONT* font, int textOption) {
	text->font = font;
	text->dialogueOption = textOption;
	switch (textOption) {
	case 0:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Ó Tália, musa singela destes campos,..");
		break;
	case 1:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Cujo ar doce inflama meus cantos rústicos,...");
		break;
	case 2:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Onde se oculta, dizei-me, por favor,...");
		break;
	case 3:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Meu cajado, meu fiel companheiro?");
		break;
	case 4:
		strcpy(text->personagem, "Dirceu");
		strcpy(text->texto, "O que o senhor disse? Cajado? Quem é Tália?");
		break;
	case 6:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Obrigado meu querido Dirceu!");
		break;
	case 7:
		strcpy(text->personagem, "Homem Velho");
		strcpy(text->texto, "Com teu generoso auxílio, poderei enfim partir em serena jornada para reaver meu cajado.");
		break;
	case 8:
		strcpy(text->personagem, "Dirceu");
		strcpy(text->texto, "Como tu chegastes aqui?");
		break;
	case 10:
		strcpy(text->personagem, "Audine");
		strcpy(text->texto, "Ouviste falar, Araminta, do homem que foi decapitado na praça pública?");
		break;
	case 11:
		strcpy(text->personagem, "Araminta");
		strcpy(text->texto, "Sim, ouvi. Sabes acaso qual era o seu nome?");
		break;
	case 12:
		strcpy(text->personagem, "Audine");
		strcpy(text->texto, "Chamavam-no Tiradentes, se bem me recordo.");
		break;
	case 13:
		strcpy(text->personagem, "Dirceu-Pensamentos");
		strcpy(text->texto, "Repousa em paz, nobre amigo. Tu que tanto lutaste pela liberdade do nosso povo...");
		break;
	case 15:
		strcpy(text->personagem, "Baltazar");
		strcpy(text->texto, "Ao que tudo indica, não desistes mesmo de minha filha…");
		break;
	case 16:
		strcpy(text->personagem, "Baltazar");
		strcpy(text->texto, "Contudo, desta feita, conceder-te-ei uma oportunidade.");
		break;
	case 17:
		strcpy(text->personagem, "Baltazar");
		strcpy(text->texto, "Permito que a desposes!");
		break;
	case 18:
		strcpy(text->personagem, "Baltazar");
		strcpy(text->texto, "Mas somente se fores capaz de completar este soneto.");
		break;
	}

	al_draw_filled_rectangle(text->x, text->y, text->x + text->width, text->y + text->height, text->boxColor);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 15, 0, text->personagem);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 35, 0, text->texto);
	al_draw_text(text->font, TEXT_COLOR, text->width - 275, text->y + 70, 0, "Pressione R para fechar o dialogo");
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 70, 0, "Pressione T ->");
}
