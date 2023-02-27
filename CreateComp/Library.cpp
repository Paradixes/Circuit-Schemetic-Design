#include "Library.h"

Library::Library(PaintWidget*& rhs)
{
    paintWidget = rhs;
}

void Library::saveImage()
{
    pngName = QFileDialog::getOpenFileName(this, tr("save"), ".", tr("Image(*.png)"));
    if(pngName.length() == 0) {
        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else {
        QMessageBox::information(NULL, tr("Path"), tr("You selected ") + pngName);
    }

    QImage image(130 * paintWidget->width() / paintWidget->height(), 130, QImage::Format_ARGB32);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);
    paintWidget->render(&painter);
    image.save(pngName);
}
