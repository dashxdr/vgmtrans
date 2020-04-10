/*
 * VGMTrans (c) 2002-2019
 * Licensed under the zlib license,
 * refer to the included LICENSE.txt file
 */

#include "KonamiPS1Seq.h"
#include <fmt/format.h>

void KonamiPS1Scanner::Scan(RawFile *file, void *info) {
    uint32_t offset = 0;
    int numSeqFiles = 0;
    while (offset < file->size()) {
        if (KonamiPS1Seq::IsKDT1Seq(file, offset)) {
            std::string name = file->tag.HasTitle()
                                    ? file->tag.title
                                    : removeExtFromPath(file->name());
            if (numSeqFiles >= 1) {
                name += fmt::format("({})", numSeqFiles + 1);
            }

            KonamiPS1Seq *newSeq = new KonamiPS1Seq(file, offset, name);
            if (newSeq->LoadVGMFile()) {
                offset += newSeq->unLength;
                numSeqFiles++;
                continue;
            } else {
                delete newSeq;
            }
        }
        offset++;
    }
}
