#include "fileerror.h"
/*This class manages the errors in the file handling
*To be added : add an object type (Horizon = 0; Layer = 1; Object = 2)
* With this object type, create a custom error code and description
*/
FileError::FileError(int type, QObject *parent) : QObject(parent)
{
    setType(type);
}

int FileError::getType() const
{
    return type;
}

void FileError::setType(int value)
{
    type = value;
    switch (value) {
    case 0:
        message = tr("FILE DOES NOT EXIST");
        break;
    case 1:
        message = tr("FILE ALREADY EXISTS");
        break;
    case 2:
        message = tr("COULD NOT OPEN FILE");
        break;
    case 3:
        message = tr("COULD NOT CLOSE FILE");
        break;
    case 4:
        message = tr("DIRECTORY ALREADY EXISTS");
        break;
    case 5:
        message = tr("DIRECTORY DOES NOT EXISTS");
        break;
    case 6:
        message = tr("COULD NOT DELETE FILE");
        break;
    case 7:
        message = tr("FILE IS ALREADY OPEN");
        break;
    case 8:
        message = tr("HORIZON ALREADY EXISTS");
        break;
    case 9:
        message = tr("LAYER ALREADY EXISTS");
        break;
    case 10:
        message = tr("OBJECT ALREADY EXISTS");
        break;
    case 11:
        message = tr("ERREUR DANS LA SUPPRESSION DU FICHIER");

    default:
        message = tr("UNKNOWN ERROR OCCURED");
        break;

    }
}

QString FileError::getMessage() const
{
    return message;
}


