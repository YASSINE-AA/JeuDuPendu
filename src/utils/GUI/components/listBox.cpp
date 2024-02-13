#include "listBox.hpp"

void ListBox::setDeleteButtonRect(const SDL_Rect &rect)
{
    deleteButtonRect = rect;
}

void ListBox::render()
{
    SDL_Color normalColor = {0, 0, 0};
    SDL_Color hoverColor = {255, 0, 0};
    SDL_Color colorWhite = {255, 255, 255};
    int x, y, addPos;

    states.getMousePosition(&x, &y);                                   // Obtient la position de la souris
    renderer.renderRectFilled(dimensions, {0, 0, 0}, {255, 255, 255}); // Rend le rectangle principal
    addPos = 45;
    renderer.renderRectFilled(addButtonDimensions, {0, 0, 0}, {255, 255, 255}); // Rend le bouton d'ajout

    for (size_t i = 0; i < wordCount; ++i)
    {
        SDL_Color color = normalColor; // Couleur normale pour chaque élément de la liste
        if (listPos + elementSpacing - dimensions.y > 0)
        {                                                                                                              // Vérifie si l'élément est dans la zone visible
            SDL_Rect elementBounds = {dimensions.x, listPos + elementSpacing + addPos, dimensions.w, originalSpacing}; // Limites de l'élément actuel
            if (x >= elementBounds.x && x <= elementBounds.x + elementBounds.w && y >= elementBounds.y && y <= elementBounds.y + elementBounds.h)
            {
                color = hoverColor;  // Change la couleur en cas de survol par la souris
                lastHoveredItem = i; // Met à jour le dernier élément survolé
                                     // Render the delete button when hovering
                int textWidth, textHeight;
                renderer.getTextSize(font, (std::to_string(i + 1) + "- " + data[i]).c_str(), &textWidth, &textHeight);
                SDL_Rect deleteButtonRect = {elementBounds.x + textWidth + 20, elementBounds.y + 5, 20, 20};
                setDeleteButtonRect(deleteButtonRect);
                renderer.renderRectFilled(deleteButtonRect, {255, 0, 0}, {255, 255, 255});
                // Render X inside the delete button
                SDL_Rect xRect1 = {deleteButtonRect.x + 5, deleteButtonRect.y + 5, 10, 10};
                SDL_Rect xRect2 = {deleteButtonRect.x + 15, deleteButtonRect.y + 5, 10, 10};
                renderer.renderLine(xRect1.x, xRect1.y, xRect1.x + xRect1.w, xRect1.y + xRect1.h, 1);
                renderer.renderLine(xRect1.x + xRect1.w, xRect1.y, xRect1.x, xRect1.y + xRect1.h, 1);
            }
            // Render text using real width
            renderer.renderFont(font, (std::to_string(i + 1) + "- " + data[i]).c_str(), color, dimensions.x + margin, listPos + elementSpacing + addPos);
        }
        elementSpacing += 40;                              // Espacement entre les éléments de la liste
        if (listPos + elementSpacing - 100 > dimensions.h) // Vérifie si la liste dépasse la zone d'affichage
            break;
    }
    renderer.renderFont(font, "Add a word", normalColor, addButtonDimensions.x + margin, addButtonDimensions.y + margin); // Rend le texte du bouton d'ajout
    addModal.render();                                                                                                    // Affiche la fenêtre modale d'ajout
    elementSpacing = 0;                                                                                                   // Réinitialise l'espacement entre les éléments de la liste
}

void ListBox::pushItem(std::string item)
{
    data.push_back(item); // Ajoute un élément à la liste
    updateParams();       // Met à jour les paramètres de la liste
}

void ListBox::removeItem(int idx)
{
    if (idx >= 0 && idx < data.size())
    {
        data.erase(data.begin() + idx); // Supprime un élément de la liste
        updateParams();                 // Met à jour les paramètres de la liste
    }
}

int ListBox::getLastHoveredItem()
{
    return lastHoveredItem; // Renvoie l'index du dernier élément survolé
}

void addWordCallback(AddModal &addModal, BinaryTree &tree, Dictionary &dictionary)
{
    std::string wordToAdd = addModal.getTextBoxValue(); // Obtient le mot à ajouter depuis la fenêtre modale
    tree.insertWord(wordToAdd);                         // Insère le mot dans l'arbre binaire
    addModal.setWord(wordToAdd);                        // Définit le mot dans la fenêtre modale
    dictionary.addToFile("dict.txt", wordToAdd);        // Ajoute le mot au fichier de dictionnaire
    addModal.sendUpdate();                              // Envoie une mise à jour à la fenêtre modale
}

void ListBox::handleEvents(SDL_Event &e)
{
    addModal.handleEvents(e); // Gère les événements de la fenêtre modale d'ajout

    if (e.type == SDL_MOUSEWHEEL && !blockEvents)
    {
        int y = e.wheel.y;
        if (y == 1 && listPos < 110)
        {
            listPos += 40; // Défilement vers le haut
        }
        else if (dimensions.y - listPos < listSize - 12 * 40)
        {
            listPos -= 40; // Défilement vers le bas
        }
        std::cout << "test" << std::endl;
    }
    else if (e.type == SDL_MOUSEBUTTONDOWN)
    {
        int mouseX, mouseY;
        states.getMousePosition(&mouseX, &mouseY);

        if (states.isBtnArea(mouseX, mouseY, deleteButtonRect))
        {
            std::cout << "test" << std::endl;
        }

        if (addModal.isClosed() && states.isBtnArea(mouseX, mouseY, addButtonDimensions))
        {
            addModal.setTitle("Add a new word");          // Définit le titre de la fenêtre modale d'ajout
            addModal.setContent("Type in a word:");       // Définit le contenu de la fenêtre modale d'ajout
            addModal.setVisibility(true);                 // Affiche la fenêtre modale d'ajout
            addModal.setAddWordCallback(addWordCallback); // Définit la fonction de rappel pour ajouter un mot
        }

        if (addModal.getUpdate())
        {
            pushItem(addModal.getWord()); // Ajoute le mot depuis la fenêtre modale à la liste
            addModal.resetUpdate();       // Réinitialise le statut de mise à jour de la fenêtre modale
        }
    }
}

void ListBox::updateParams()
{
    wordCount = data.size();                // Met à jour le nombre d'éléments dans la liste
    listSize = wordCount * originalSpacing; // Met à jour la taille de la liste
}
