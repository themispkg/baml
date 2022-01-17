#!/bin/bash

#    baml ain't markup language - baml 1.0.0
#    Copyright (C) 2021  lazypwny751
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <https://www.gnu.org/licenses/>.

baml:parse2bash() {
    # Usage:
    # . baml.sh
    # baml:parse2bash "example.baml"
    #< test=( 'deneme1' 'deneme2' '123' )
    #< deneme123=( 'tamam bu' 'oldu' )

    # Using argv = 1

    # Exit status:
    # 1: missing dependencity
    # 2: file not found

    # Check dependencies
    command -v awk &> /dev/null || return 1
    command -v seq &> /dev/null || return 1
    command -v sed &> /dev/null || return 1
    command -v tr &> /dev/null || return 1
    
    # Define arguments
    local VARIABLE_TOKEN=";"
    local ARRAY_TOKEN="->"

    # Main code block
    if [[ -f "${1}" ]] ; then
        local BAML_MAXLINE="$(awk 'END { print NR }' "${1}")"
        for BAML_LINENO in $(seq 1 "${BAML_MAXLINE}") ; do
            local BAML_SETLINE="$(awk "NR==${BAML_LINENO}" "${1}")"
            if  [[ "$(echo "${BAML_SETLINE}" | awk '{printf $1}')" = *"${VARIABLE_TOKEN}" ]] ; then
                echo -n "$(echo "${BAML_SETLINE}" | awk '{printf $1}' | tr "${VARIABLE_TOKEN}" "=")( "
                while true ; do
                    BAML_LINENO="$(("${BAML_LINENO}" + 1))"
                    local BAML_SETLINE="$(awk "NR==${BAML_LINENO}" "${1}")"
                    if [[ "$(echo "${BAML_SETLINE}" | awk '{print $1}')" = "${ARRAY_TOKEN}" ]] ; then
                        echo -n "'$(echo "${BAML_SETLINE}" | awk '{$1=""; print $0}' | sed 's/ //' )' "
                    elif [[ "$(echo "${BAML_SETLINE}" | awk '{printf $1}')" = *"${VARIABLE_TOKEN}" ]] ; then
                        break
                    elif [[ "${BAML_LINENO}" -ge "${BAML_MAXLINE}" ]] ; then
                        echo ")"
                        return 0
                    fi
                done
                echo ")"
            fi
        done
    else
        return 2
    fi
}

baml:parse2py() {
    # coming soon
    :
}

baml:parse2bash "${1}"