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

#include "LowAudioLatency.h"

#include <QAudioDevice>
#include <QMediaDevices>

#include "../Logger.h"
#include "../Application.h"

namespace Core::LowAudioLatency {

Controller::Controller(QObject *parent) : QObject{parent}
{
    connect(this, &Controller::ControlSafely, this, &Controller::Control);

    _initTimer.callOnTimeout([this] {
        if (Initialize()) {
            _initTimer.stop();
        }
    });

    if (!Initialize()) {
        // retry later
        _initTimer.start(kRetryInterval);
    }
}

bool Controller::Initialize()
{
    // issue #20
    //
    // Constructing `QMediaPlayer` when no audio output device is enabled will cause `play` to
    // continually raise errors and is unrecoverable.
    if (QMediaDevices::audioOutputs().empty()) {
        LOG(Warn, "LowAudioLatency: Try to init, but no audio output device is enabled.");
        return false;
    }

    _mediaPlayer = std::make_unique<QMediaPlayer>();

    connect(
        _mediaPlayer.get(), &QMediaPlayer::errorOccurred, this,
        [this](QMediaPlayer::Error error, const QString &) { OnError(error); });

    _mediaPlayer->setSource(QUrl{"qrc:/Resource/Audio/Silence.mp3"});
    _mediaPlayer->setLoops(QMediaPlayer::Infinite);

    _inited = true;

    LOG(Info, "LowAudioLatency: Init successful. _enabled: {}", _enabled);

    if (_enabled) {
        Control(true);
    }

    return true;
}

void Controller::Control(bool enable)
{
    LOG(Info, "LowAudioLatency::Controller Control: {}, _inited: {}", enable, _inited);

    if (_inited) {
        if (enable) {
            _mediaPlayer->play();
        }
        else {
            _mediaPlayer->stop();
        }
    }

    _enabled = enable;
}

void Controller::OnError(QMediaPlayer::Error error)
{
    LOG(Warn, "LowAudioLatency::Controller error: {}. Reinit later.", error);

    _mediaPlayer->stop();
    _inited = false;
    _initTimer.start(kRetryInterval);
}

} // namespace Core::LowAudioLatency
