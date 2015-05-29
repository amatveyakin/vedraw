#pragma once

#include "utils/error_handling.h"


void ShowError( const Exception& e );

#define CATCH_SHOW_ERROR \
    CATCH { \
        ShowError( e ); \
    }
