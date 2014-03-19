/*
 * MaskedImageView.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: rodrigopex
 */

#include "MaskedImageView.hpp"

#include <qt4/QtGui/QImage>
#include <qt4/QtGui/QPainter>
#include <qt4/QtGui/QPainterPath>
#include <bb/ImageData>

MaskedImageView::MaskedImageView(bb::cascades::Container *parent) :
		bb::cascades::ImageView(parent) {
}

MaskedImageView::~MaskedImageView() {
}

QUrl MaskedImageView::imageSource() const {
	return m_imageSource;
}

bb::ImageData fromQImage(const QImage &qImage)
{
    bb::ImageData imageData(bb::PixelFormat::RGBA_Premultiplied, qImage.width(), qImage.height());

    unsigned char *dstLine = imageData.pixels();
    for (int y = 0; y < imageData.height(); y++) {
        unsigned char * dst = dstLine;
        for (int x = 0; x < imageData.width(); x++) {
            QRgb srcPixel = qImage.pixel(x, y);
            *dst++ = qRed(srcPixel);
            *dst++ = qGreen(srcPixel);
            *dst++ = qBlue(srcPixel);
            *dst++ = qAlpha(srcPixel);
        }
        dstLine += imageData.bytesPerLine();
    }
    return imageData;
}

void MaskedImageView::setMaskedImageSource(const QUrl &source) {
	QString filePath;
	if(source.scheme() == "asset" || source.scheme() == "") {
		filePath = "app/native/assets";
	}
	filePath.append(source.path());
	QImage rawImage = QImage(filePath);
	QImage maskedImage(QSize(rawImage.size().width(), rawImage.size().height()),
				QImage::Format_ARGB32_Premultiplied);
	maskedImage.fill(qRgba(0, 0, 0, 255));

	/*This is the mask. If you want to create other shape
	 * for mask is just necessary to build another path. Enjoy it!
	 * Begin - Mask */
	QPainterPath path;
	path.addEllipse(
			QRect(0, 0, maskedImage.size().width(), maskedImage.size().height()));
	/* End - Mask */

	QPainter m_ctx;
	m_ctx.begin(&maskedImage);
	m_ctx.setBrush(QBrush(QColor(qRgba(0,0,0,0)), Qt::SolidPattern));
	m_ctx.setRenderHint(QPainter::Antialiasing, true);
	m_ctx.setClipping(true);
	m_ctx.setClipPath(path);
	m_ctx.drawImage(QPoint(0, 0), rawImage);
	m_ctx.end();

	bb::cascades::Image image(fromQImage(maskedImage));
	bb::cascades::ImageView::setImage(image);
}

