#!/bin/bash

cd ../matrix/;
make;

cd ../stick/;
make;

cd ../kick/kick.cui/;
make;

mv kick ../;
cd ../;