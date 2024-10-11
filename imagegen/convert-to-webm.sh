#!/bin/bash

ffmpeg -i $1 -c:v libvpx-vp9 -crf 30 -b:v 0 -b:a 128k -c:a libopus output.webm

