/*********************************************************************************
 *
 * Inviwo - Interactive Visualization Workshop
 *
 * Copyright (c) 2013-2015 Inviwo Foundation
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 *********************************************************************************/

#ifndef IVW_FILEEXTENSION_H
#define IVW_FILEEXTENSION_H

#include <inviwo/core/common/inviwocoredefine.h>
#include <inviwo/core/common/inviwo.h>
#include <inviwo/core/util/stdextensions.h>

namespace inviwo {

class IVW_CORE_API FileExtension : public Serializable {
public:
    FileExtension();
    FileExtension(const FileExtension&) = default;
    FileExtension& operator=(const FileExtension&) = default;
    FileExtension(std::string extension, std::string description);
    virtual ~FileExtension() = default;

    /** 
     * \brief extracts a FileExtension object from a string. This function assumes
     * that the extension is given within the right most parentheses.
     * 
     * @param str Input string  formed like "Text files (*.txt)".
     * @return FileExtension object created from the information given in the input string.
     */
    static FileExtension createFileExtensionFromString(const std::string &str);
    std::string toString() const;

    virtual void serialize(Serializer& s) const override;
    virtual void deserialize(Deserializer& d) override;


    std::string extension_; ///< File extension in lower case letters.
    std::string description_;

    friend bool operator==(const FileExtension&, const FileExtension&);
};

bool operator==(const FileExtension&, const FileExtension&);

} // namespace

namespace std {
    template<>
    struct hash<inviwo::FileExtension>
    {
        size_t operator()(const inviwo::FileExtension& f) const {
            size_t h = 0;
            inviwo::util::hash_combine(h, f.extension_);
            inviwo::util::hash_combine(h, f.description_);
            return h;
        }
    };
}

#endif // IVW_FILEEXTENSION_H

