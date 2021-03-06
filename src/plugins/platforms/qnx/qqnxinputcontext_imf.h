/***************************************************************************
**
** Copyright (C) 2011 - 2012 Research In Motion
** Contact: http://www.qt-project.org/legal
**
** This file is part of the plugins of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and Digia.  For licensing terms and
** conditions see http://qt.digia.com/licensing.  For further information
** use the contact form at http://qt.digia.com/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 as published by the Free Software
** Foundation and appearing in the file LICENSE.LGPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU Lesser General Public License version 2.1 requirements
** will be met: http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Digia gives you certain additional
** rights.  These rights are described in the Digia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#ifndef QQNXINPUTCONTEXT_H
#define QQNXINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>

#include <QtCore/QLocale>
#include <QtCore/QMetaType>
#include <qpa/qplatformintegration.h>

#include "imf/imf_client.h"
#include "imf/input_control.h"

QT_BEGIN_NAMESPACE

class QQnxAbstractVirtualKeyboard;

class QQnxInputContext : public QPlatformInputContext
{
    Q_OBJECT
public:
    explicit QQnxInputContext(QQnxAbstractVirtualKeyboard &keyboard);
    ~QQnxInputContext();

    bool isValid() const;

    bool filterEvent(const QEvent *event);
    void reset();
    void update(Qt::InputMethodQueries);
    bool handleKeyboardEvent(int flags, int sym, int mod, int scan, int cap);

    void showInputPanel();
    void hideInputPanel();
    bool isInputPanelVisible() const;

    QLocale locale() const;
    void setFocusObject(QObject *object);

protected:
    // Filters only for IMF events.
    bool eventFilter(QObject *obj, QEvent *event);

private Q_SLOTS:
    void keyboardVisibilityChanged(bool visible);
    void keyboardLocaleChanged(const QLocale &locale);

private:
    // IMF Event dispatchers
    bool dispatchFocusEvent(FocusEventId id, int hints = Qt::ImhNone);
    bool dispatchRequestSoftwareInputPanel();
    bool dispatchCloseSoftwareInputPanel();
    int32_t processEvent(event_t *event);

    void closeSession();
    void openSession();
    bool hasSession();
    void endComposition();
    void setComposingText(QString const &composingText);
    bool hasSelectedText();

    // IMF Event handlers - these events will come in from QCoreApplication.
    int32_t onBeginBatchEdit(input_session_t *ic);
    int32_t onClearMetaKeyStates(input_session_t *ic, int32_t states);
    int32_t onCommitText(input_session_t *ic, spannable_string_t *text, int32_t new_cursor_position);
    int32_t onDeleteSurroundingText(input_session_t *ic, int32_t left_length, int32_t right_length);
    int32_t onEndBatchEdit(input_session_t *ic);
    int32_t onFinishComposingText(input_session_t *ic);
    int32_t onGetCursorCapsMode(input_session_t *ic, int32_t req_modes);
    int32_t onGetCursorPosition(input_session_t *ic);
    extracted_text_t *onGetExtractedText(input_session_t *ic, extracted_text_request_t *request, int32_t flags);
    spannable_string_t *onGetSelectedText(input_session_t *ic, int32_t flags);
    spannable_string_t *onGetTextAfterCursor(input_session_t *ic, int32_t n, int32_t flags);
    spannable_string_t *onGetTextBeforeCursor(input_session_t *ic, int32_t n, int32_t flags);
    int32_t onPerformEditorAction(input_session_t *ic, int32_t editor_action);
    int32_t onReportFullscreenMode(input_session_t *ic, int32_t enabled);
    int32_t onSendEvent(input_session_t *ic, event_t *event);
    int32_t onSendAsyncEvent(input_session_t *ic, event_t *event);
    int32_t onSetComposingRegion(input_session_t *ic, int32_t start, int32_t end);
    int32_t onSetComposingText(input_session_t *ic, spannable_string_t *text, int32_t new_cursor_position);
    int32_t onSetSelection(input_session_t *ic, int32_t start, int32_t end);
    int32_t onForceUpdate();

    int m_lastCaretPos;
    bool m_isComposing;
    QString m_composingText;
    bool m_inputPanelVisible;
    QLocale m_inputPanelLocale;
    QQnxAbstractVirtualKeyboard &m_virtualKeyboad;
};

Q_DECLARE_METATYPE(extracted_text_t*)

QT_END_NAMESPACE

#endif // QQNXINPUTCONTEXT_H
