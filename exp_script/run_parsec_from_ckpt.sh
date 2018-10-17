#!/bin/bash

# PARSEC benchmarks

#Need to export GEM5_PATH
if [ -z ${GEM5_PATH+x} ];
then
    echo "GEM5_PATH is unset";
    exit
else
    echo "GEM5_PATH is set to '$GEM5_PATH'";
fi


#Need to export M5_PATH
if [ -z ${M5_PATH+x} ];
then
    echo "M5_PATH is unset. M5_PATH is the path the full disk image.";
    exit
else
    echo "M5_PATH is set to '$M5_PATH'";
fi


WORKLOAD=blackscholes
INPUT_SIZE=test
#simmedium
SCHEME=FuturisticSafeInvisibleSpec
#FuturisticSafeFence
CORE_NUM=4
ISA=arm


CKPT_OUT_DIR=$GEM5_PATH/../gem5_ckpt/$WORKLOAD-$CORE_NUM-$INPUT_SIZE-$ISA
OUT_DIR=$GEM5_PATH/output/$WORKLOAD-$CORE_NUM-$INPUT_SIZE-$ISA-$SCHEME

CONFIG_FILE=$GEM5_PATH/configs/example/fs.py 

echo "scirpt file: " $SCRIPT_FILE
echo "checkpoint direcotory: " $CKPT_OUT_DIR
echo "output directory: " $OUT_DIR

echo "clean up old files"
if [ -d "$OUT_DIR" ]
then
    rm -r $OUT_DIR
fi

echo "create output directory"
mkdir -p $OUT_DIR

    echo "run arm simulator"
    # always use opt to test simulator locally, otherwise messages may not print
    $GEM5_PATH/build/ARM_MESI_Two_Level/gem5.opt \
        --outdir=$OUT_DIR     $CONFIG_FILE \
        --checkpoint-dir=$CKPT_OUT_DIR \
        --script=$SCRIPT_FILE \
        --machine-type=VExpress_EMM64 \
        --kernel=$M5_PATH/binaries/vmlinux.aarch64.20140821 \
        --dtb-file=$M5_PATH/binaries/vexpress.aarch64.20140821.dtb \
        --disk-image=$M5_PATH/disks/aarch64-ubuntu-trusty-headless.img \
        --num-cpus=$CORE_NUM --mem-size=2GB --num-l2caches=$CORE_NUM \
        --num-dirs=$CORE_NUM --network=simple --topology=Mesh_XY --mesh-rows=4 \
        --l1d_assoc=8 --l2_assoc=16 --l1i_assoc=4 \
        --checkpoint-restore=1 --ruby --cpu-type=DerivO3CPU  \
        --needsTSO=0 --scheme=$SCHEME &> $OUT_DIR/log.txt &


