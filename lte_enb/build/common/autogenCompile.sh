ENB_INSTALL_DIR=$PWD/../../
TENB_COMMPLAT_DIR=$ENB_INSTALL_DIR/src/tenb_commonplatform/

cd $TENB_COMMPLAT_DIR/software/libs/common/mib-common/

make PRODUCT=generic HARDWARE=generic BUILD=i686-linux 

cd $TENB_COMMPLAT_DIR/software/libs/mib-core/
make PRODUCT=generic HARDWARE=generic BUILD=i686-linux 

cp -f $TENB_COMMPLAT_DIR/software/libs/common/mib-common/../../../libs/platform/home-fap/radisys-home-fap-mib-nvcheck-temp.xml $TENB_COMMPLAT_DIR/software/libs/common/mib-common/../../../libs/platform/home-fap/radisys-home-fap-mib-nvcheck.xml

cd $TENB_COMMPLAT_DIR/software/libs/common/mib-common/
make PRODUCT=generic HARDWARE=generic BUILD=i686-linux 

cd $TENB_COMMPLAT_DIR/software/libs/mib-core/
make PRODUCT=generic HARDWARE=generic BUILD=i686-linux 

cd $TENB_COMMPLAT_DIR/software/apps/utilities/data-model-code-generator
python DataModelCodeGenerator.py
