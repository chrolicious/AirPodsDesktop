//
// AirPodsDesktop - AirPods Desktop User Experience Enhancement Program.
// Copyright (C) 2021-2022 SpriteOvO
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.
//

#pragma once

#include <cstdint>

namespace Config {

#define CONFIG_VERSION_STRING           "0.4.1"
#define CONFIG_WINRC_VERSION_NUMBERS    0, 4, 1, 0
#define CONFIG_WINRC_VERSION_STRING     CONFIG_VERSION_STRING ".0"
#define CONFIG_PROGRAM_NAME             "AirPodsDesktop"
#define CONFIG_DESCRIPTION              "AirPods desktop user experience enhancement program"
#define CONFIG_COPYRIGHT                "Copyright © 2021-2022 SpriteOvO. All rights reserved."
#define CONFIG_CPACK_SYSTEM_NAME        "win64"
#define CONFIG_URL_REPO                 "https://github.com/SpriteOvO/" CONFIG_PROGRAM_NAME
#define CONFIG_URL_ISSUES               CONFIG_URL_REPO "/issues"
#define CONFIG_URL_RELEASES             CONFIG_URL_REPO "/releases"
#define CONFIG_URL_LICENSE              CONFIG_URL_REPO "/blob/main/LICENSE"
#define CONFIG_URL_CURRENT_RELEASE      CONFIG_URL_RELEASES "/tag/" CONFIG_VERSION_STRING

constexpr inline auto ProgramName = CONFIG_PROGRAM_NAME;
constexpr inline auto UrlRepository = CONFIG_URL_REPO;
constexpr inline auto UrlIssues = CONFIG_URL_ISSUES;
constexpr inline auto UrlReleases = CONFIG_URL_RELEASES;
constexpr inline auto UrlLicense = CONFIG_URL_LICENSE;
constexpr inline auto UrlCurrentRelease = CONFIG_URL_CURRENT_RELEASE;
constexpr inline auto License = "GPLv3";
constexpr inline auto Copyright = CONFIG_COPYRIGHT;
constexpr inline auto Description = CONFIG_DESCRIPTION;
constexpr inline auto QrcIconSvg = ":/Resource/Image/Icon.svg";
constexpr inline auto TranslationLocales = "de_DE;fr_FR;ja_JP;ko_KR;ru_RU;zh_CN;zh_TW";

namespace Version {

constexpr inline uint32_t Major = 0;
constexpr inline uint32_t Minor = 4;
constexpr inline uint32_t Patch = 1;

constexpr inline auto String = CONFIG_VERSION_STRING;

} // namespace Version
} // namespace Config
