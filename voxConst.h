#ifndef VOXCONST_H
#define VOXCONST_H

#include <QString>
#include <QList>
#include <QRegExp>
#include <QSize>

namespace voxConst {

const QString voxHeader = "TB+PO";

const int cardAbs = 25;
const int cardNo = 2;

//int globalIDcount = 0;

const int SIZE_TO_ADD = 6;
const QString dictFile = "/meta/dict.vox";

enum languages{
    ger,
    fra,
    ita,
    por,
    spa,
};

enum natLanguages{
    eng
};

const QList<QString> umGermanLC = QList<QString>() << "ä" << "ö" << "ü"  << "ß";
const QList<QString> umGermanUC = QList<QString>() << "Ä" << "Ö" << "Ü" << "ß";

//to do upper lower case for other languages
const QList<QString> umFrench = QList<QString>() << "À" << "Â" << "Æ" << "È" << "É" << "Ê" << "Ë" << "Î" << "Ï" << "Ô" << "Ù" << "Û" << "Ü" << "Ç" << "Œ" << "à" << "â" << "æ" << "è" << "é" << "ê" << "ë" << "î" << "ï" << "ô" << "ù" << "û" << "ü" << "ç" << "œ";
const QList<QString> umSpanish = QList<QString>() << "Á" << "É" << "Í" << "Ó" << "Ú" << "Ü" << "Ñ" << "¿" << "¡" << "á" << "é" << "í" << "ó" << "ú" << "ü" << "ñ";
const QList<QString> umPortuguese = QList<QString>() << "Ã" << "Á" << "Â" << "À" << "É" << "Ê" << "Í" << "Õ" << "Ó" << "Ô" << "Ú" << "Ü" << "Ç" << "ã" << "á" << "â" << "à" << "é" << "ê" << "í" << "õ" << "ó" << "ô" << "ú" << "ü" << "ç";
const QList<QString> umItalian = QList<QString>() << "À" << "Á" << "È" << "É" << "Ì" << "Í" << "Ò" << "Ó" << "Ù" << "Ú" << "à" << "á" << "è" << "é" << "ì" << "í" << "ò" << "ó" << "ù" << "ú";
//}

const QRegExp rxLEdit("^term(\\d+)_LEdit$");

const QSize homeFlagSize = QSize(80, 45);

}

#endif // VOXCONST_H
