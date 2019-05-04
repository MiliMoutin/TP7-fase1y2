#include "ExternalHandler.h"

ExternalHandler::ExternalHandler() {
	this->handler = lcdInit(DEVICE);
}

ExternalHandler::~ExternalHandler() {
	FT_Close(*handler);
}
void ExternalHandler::writeDR(BYTE byte) {
	lcdWriteDR(this->handler, byte);
}

void ExternalHandler::writeIR(BYTE byte) {
	lcdWriteIR(this->handler, byte);
}