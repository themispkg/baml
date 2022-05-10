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

export HEADERTOKEN=";" ENTRYTOKEN="->"
export IFS="" setline="" counter="0"

case "${1}" in
    --[hH][eE][lL][pP]|-[hH])
        exit 0
    ;;
    --[vV][eE][rR][sS][iI][oO][nN]|-[vV])
        exit 0
    ;;
    --[pP][yY][tT][hH][oO][nN]|-[pP])
        for i in ${@:2} ; do
            if (file "${i}" | grep -w "ASCII text") &> /dev/null ; then
                baml:parse --python "${i}"
            fi
        done
    ;;  
    *)
        for i in ${@:1} ; do
            export index=()
            if (file "${i}" | grep -w "ASCII text") &> /dev/null ; then
                while read -r setline || [[ -n "${setline}" ]] ; do
                    export index+=("${setline/" "/}")
                done < "${i}"

                # idk, when i use for loop it break the script
                # and there is no solutions.
                while true ; do
                    if [[ "${index[counter]}" = *${HEADERTOKEN} ]] ; then
                        echo -n "${index[counter]/${HEADERTOKEN}/}=("
                        (
                            while true ; do
                                export counter="$((${counter} + 1))"
                                if [[ "${index[counter]}" = *${ENTRYTOKEN}* ]] ; then
                                    echo -n " '$(echo "${index[counter]/${ENTRYTOKEN}/}" | sed 's/^ *//')'"
                                elif [[ "${index[counter]}" = *${HEADERTOKEN} ]] ; then
                                    echo ")"
                                    export counter="$((${counter} - 1))"
                                    break
                                elif [[ "${counter}" -ge "${#index[@]}" ]] ; then
                                    echo ")"
                                    break
                                fi
                            done
                        )
                    fi
                    counter="$((${counter} + 1))"
                    [[ "${counter}" -ge "${#index[@]}" ]] && break
                done
            fi
        done
    ;;
esac