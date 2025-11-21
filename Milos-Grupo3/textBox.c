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
		strcpy(text->texto, "Graças a sua ajuda, poderei sair em jornada para encontrar meu cajado");
		break;
	case 8:
		strcpy(text->personagem, "Dirceu");
		strcpy(text->texto, "Como você chegou aqui?");
		break;
	case 10:
		strcpy(text->personagem, "Audine");
		strcpy(text->texto, "Você ficou sabendo daquele homen que decaptaram em praça pública?");
		break;
	case 11:
		strcpy(text->personagem, "Araminta");
		strcpy(text->texto, "Sim fiquei, sabe quem é sabe o nome dele?");
		break;
	case 12:
		strcpy(text->personagem, "Audine");
		strcpy(text->texto, "Acho que era Tiradendes o apelido dele.");
		break;
	case 13:
		strcpy(text->personagem, "Dirceu-Pensamentos");
		strcpy(text->texto, "Descanse em paz amigo.");
		break;
	case 15:
		strcpy(text->personagem, "Marcelos");
		strcpy(text->texto, "Pelo visto você não desiste mesmo da minha filha...");
		break;
	case 16:
		strcpy(text->personagem, "Marcelos");
		strcpy(text->texto, "Mas dessa vês eu lhe darei uma chance...");
		break;
	case 17:
		strcpy(text->personagem, "Marcelos");
		strcpy(text->texto, "Eu te deixo casar com minha filha!!!");
		break;
	case 18:
		strcpy(text->personagem, "Marcelos");
		strcpy(text->texto, "Mas apenas se você completar esse poema");
		break;
	}

	al_draw_filled_rectangle(text->x, text->y, text->x + text->width, text->y + text->height, text->boxColor);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 15, 0, text->personagem);
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 35, 0, text->texto);
	al_draw_text(text->font, TEXT_COLOR, text->width - 275, text->y + 70, 0, "Pressione R para fechar o dialogo");
	al_draw_text(text->font, TEXT_COLOR, text->x + 25, text->y + 70, 0, "Pressione T ->");
}
