/**
 * $Source: /backup/cvsroot/project/pnids/zdk/zls/zvm/InstructionCode.hpp,v $
 *
 * $Date: 2001/08/11 18:54:42 $
 *
 * $Revision: 1.3 $
 *
 * $Name:  $
 *
 * $Author: zls $
 *
 * Copyright(C) since 1998 by Albert Zheng - 郑立松, All Rights Reserved.
 *
 * lisong.zheng@gmail.com
 *
 * $State: Exp $
 */


#ifndef _ZLS_zvm_InstructionCode_hpp_
#define _ZLS_zvm_InstructionCode_hpp_

#include <zls/zvm/Manifest.hpp>


ZLS_BEGIN_NAMESPACE(zvm)


/**
 * @file
 * @brief ZVM Version 2.0 指令设计.

<pre>

一、ZVM的指令码大小
    ZVM的指令码大小为一个UWORD型，由于ZVM的指令基本上都是直接在指令中将数据类型
区别出来，所以通常指令码的高字节是指令基码，而低字节是ZVM的数据类型的signature（
注意：总是大写字母的）.


二、ZVM的变量种类
    有两种变量：global variable、stack variable（local variable、local reference
variable、value argument和reference argument）.


三、ZVM的各种操作的操作数的表现形式
    操作数的表现形式有两种：value和address.
    (1)bool等简单类型
       (a)在进行+、-等二元和一元操作时，都采用value形式.
       (b)在向function传递reference argument时，才采用address形式.
    (2)string等Object类型
       (a)在进行+、-等二元和一元操作时，都采用address形式.
       (b)在向function传递reference argument时，也采用address形式.
       (c)在向function传递value argument时，才采用value形式.


四、取值指令
    基本上所有的load value指令都有一个操作数来指明"源"，只有当"源"是table element
时，才使用没有操作数的load value指令，此时"源table"的地址在stack上被指明了.

注：如果将以下形式的load value指令想象为"数据类型LoadGlobalVariableValue"，例如：
    "boolLoadGlobalVariableVale"，则就比较好理解了.

(1)global variable
--------------------------------------------------------------------------------
loadGlobalVariableValue 'signature-of-bool' variable_index(大小为sizeof(UDWORD))
loadGlobalVariableValue 'signature-of-byte' variable_index
loadGlobalVariableValue 'signature-of-sdword' variable_index
loadGlobalVariableValue 'signature-of-udword' variable_index
loadGlobalVariableValue 'signature-of-sqword' variable_index
loadGlobalVariableValue 'signature-of-uqword' variable_index
loadGlobalVariableValue 'signature-of-double' variable_index
loadGlobalVariableValue 'signature-of-string' variable_index
  注：string是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadGlobalVariableValue 'signature-of-rope' variable_index
  注：rope是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadGlobalVariableValue 'signature-of-ipv4address' variable_index
  注：ipv4address是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadGlobalVariableValue 'signature-of-pport' variable_index
  注：pport是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadGlobalVariableValue 'signature-of-table-prefix' variable_index
  注：table是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
--------------------------------------------------------------------------------

(2)local variable和value argument
--------------------------------------------------------------------------------
loadStackVariableValue 'signature-of-bool' bp_offset(大小为SWORD)
loadStackVariableValue 'signature-of-byte' bp_offset
loadStackVariableValue 'signature-of-sdword' bp_offset
loadStackVariableValue 'signature-of-udword' bp_offset
loadStackVariableValue 'signature-of-sqword' bp_offset
loadStackVariableValue 'signature-of-uqword' bp_offset
loadStackVariableValue 'signature-of-double' bp_offset
loadStackVariableValue 'signature-of-string' bp_offset
  注：string是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadStackVariableValue 'signature-of-rope' bp_offset
  注：rope是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadStackVariableValue 'signature-of-ipv4address' bp_offset
  注：ipv4address是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadStackVariableValue 'signature-of-pport' bp_offset
  注：pport是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadStackVariableValue 'signature-of-table-prefix' bp_offset
  注：table是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
--------------------------------------------------------------------------------

(3)local reference variable和reference arugment
--------------------------------------------------------------------------------
indirectLoadStackVariableValue 'signature-of-bool' bp_offset
indirectLoadStackVariableValue 'signature-of-byte' bp_offset
indirectLoadStackVariableValue 'signature-of-sdword' bp_offset
indirectLoadStackVariableValue 'signature-of-udword' bp_offset
indirectLoadStackVariableValue 'signature-of-sqword' bp_offset
indirectLoadStackVariableValue 'signature-of-uqword' bp_offset
indirectLoadStackVariableValue 'signature-of-double' bp_offset
indirectLoadStackVariableValue 'signature-of-string' bp_offset
  注：string是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
indirectLoadStackVariableValue 'signature-of-rope' bp_offset
  注：rope是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
indirectLoadStackVariableValue 'signature-of-ipv4address' bp_offset
  注：ipv4address是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
indirectLoadStackVariableValue 'signature-of-pport' bp_offset
  注：pport是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
indirectLoadStackVariableValue 'signature-of-table-prefix' bp_offset
  注：table是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
--------------------------------------------------------------------------------

(4)table element
--------------------------------------------------------------------------------
注：如果将以下形式的load element value指令想象为"load表数据类型TableElementValueBy键数据类型"，
    例如："loadBoolTableElementValeBySDWORD"，则就比较好理解了.
注：在load element value指令的前面一定有两条类似如下的指令：
        "load address of table"
        "load value or address of table key"

loadBoolTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadByteTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadSDWORDTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadUDWORDTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadSQWORDTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadUQWORDTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadDoubleTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
loadStringTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
  注：string是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadRopeTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
  注：rope是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadIPv4AddressTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
  注：ipv4address是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
loadPPortTableElementValue '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element value]
  注：ipv4address是object，因此load value要进行deep copy
  注：该指令只被用在向function传递value argument时
--------------------------------------------------------------------------------

(5)Object的中间计算结果
--------------------------------------------------------------------------------
注：这些间接取值的指令用来将Object型变量进行计算后的结果（一个在ZVM stack顶的
    object-address）转换为向function传递value argument所需要的object-value形式.

indirectLoadValueFromAddress 'signature-of-string'
indirectLoadValueFromAddress 'signature-of-rope'
indirectLoadValueFromAddress 'signature-of-ipv4address'
indirectLoadValueFromAddress 'signature-of-pport'
indirectLoadValueFromAddress 'signature-of-table'
--------------------------------------------------------------------------------


五、取地址指令
    基本上所有的load address指令都有一个TZVMIndex型的操作数来指明"源"，只有当"源"
是table element时，才使用没有操作数的load address指令，此时"源table"的地址在stack
上被指明了.

注：如果将以下形式的load address指令想象为"数据类型LoadGlobalVariableAddress"，例如：
    "boolLoadGlobalVariableAddress"，则就比较好理解了.

(1)global variable
--------------------------------------------------------------------------------
loadGlobalVariableAddress 'signature-of-bool' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.b)
loadGlobalVariableAddress 'signature-of-byte' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.uch)
loadGlobalVariableAddress 'signature-of-sdword' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.sdw)
loadGlobalVariableAddress 'signature-of-udword' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.udw)
loadGlobalVariableAddress 'signature-of-sqword' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.sqw)
loadGlobalVariableAddress 'signature-of-uqword' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.uqw)
loadGlobalVariableAddress 'signature-of-double' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.df)
loadGlobalVariableAddress 'signature-of-string' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.pciString)
  注：虽然string是object，内部实现已经是采用pointer了，但是为了语义上的统一，
      我还是决定采用pointer of pointer的方式，这也可以避免以后有意想不到的边界
      效应：当那个CSlot.pciString已经指向了另一个地址了，而以前的pointer-copy者
      却还在继续指向已经被free的地址!
loadGlobalVariableAddress 'signature-of-rope' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.pciRope)
  注：虽然rope是object，内部实现已经是采用pointer了，但是为了语义上的统一，
      我还是决定采用pointer of pointer的方式，这也可以避免以后有意想不到的边界
      效应：当那个CSlot.pciRope已经指向了另一个地址了，而以前的pointer-copy者
      却还在继续指向已经被free的地址!
loadGlobalVariableAddress 'signature-of-ipv4address' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.pciIPv4Address)
  注：同string
loadGlobalVariableAddress 'signature-of-pport' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.pciPPort)
  注：同string
loadGlobalVariableAddress 'signature-of-table-prefix' variable_index
  注：CSlot.pvAddress = &(这个global variable的CSlot.pciTable)
  注：同string
--------------------------------------------------------------------------------

(2)local variable和value argument
--------------------------------------------------------------------------------
loadStackVariableAddress 'signature-of-bool' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.b)
loadStackVariableAddress 'signature-of-byte' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.uch)
loadStackVariableAddress 'signature-of-sdword' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.sdw)
loadStackVariableAddress 'signature-of-udword' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.udw)
loadStackVariableAddress 'signature-of-sqword' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.sqw)
loadStackVariableAddress 'signature-of-uqword' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.uqw)
loadStackVariableAddress 'signature-of-double' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.df)
loadStackVariableAddress 'signature-of-string' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.pciString)
  注：虽然string是object，内部实现已经是采用pointer了，但是为了语义上的统一，
      我还是决定采用pointer of pointer的方式.
loadStackVariableAddress 'signature-of-rope' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.pciRope)
  注：虽然rope是object，内部实现已经是采用pointer了，但是为了语义上的统一，
      我还是决定采用pointer of pointer的方式.
loadStackVariableAddress 'signature-of-ipv4address' bp_offset
  注：CSlot.pvAddress = &(这个stack variable的CSlot.pciIPv4Address)
  注：同string
loadStackVariableAddress 'signature-of-pport' bp_offset
  注：CSlot.pvAddress = &(这个Stack variable的CSlot.pciPPort)
  注：同string
loadStackVariableAddress 'signature-of-table-prefix' bp_offset
  注：CSlot.pvAddress = &(这个Stack variable的CSlot.pciTable)
  注：同string
--------------------------------------------------------------------------------

(3)local reference variable和reference argument
--------------------------------------------------------------------------------
loadReferenceStackVariableReferenceToAddress bp_offset
  注：取得local reference variable或reference argument中的reference to address
  注：由于local reference variable或reference argument这个slot内的东西已经是
      address了，所以这个指令其实只是再将这个slot按位copy到一个新slot而已.
--------------------------------------------------------------------------------

(4)table element
--------------------------------------------------------------------------------
loadBoolTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
  stack细节：
    指令执行之前
	    CSlot {
	      void * pvAddress = &(CSlot-of-variable.pciTable);
	    };
	    CSlot {
	      bool b = CSlot-of-variable.b;
	      或
	      UCHAR uch = CSlot-of-variable.uch;
	      或
	      ...
	      或
	      void * pvAddress = &(CSlot-of-key-variable.对象型member);
	    };

    指令执行之后
	    CSlot {
	      void * pvAddress = &(CSlot-of-element.b);
	    };

loadByteTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadSDWORDTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadUDWORDTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadSQWORDTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadUQWORDTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadDoubleTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadStringTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
  stack细节：
    指令执行之前
	    CSlot {
	      void * pvAddress = &(CSlot-of-variable.pciTable);
	    };
	    CSlot {
	      bool b = CSlot-of-variable.b;
	      或
	      UCHAR uch = CSlot-of-variable.uch;
	      或
	      ...
	      或
	      void * pvAddress = &(CSlot-of-key-variable.对象型member);
	    };

    指令执行之后
	    CSlot {
	      void * pvAddress = &(CSlot-of-element.pciString);
	    };
loadRopeTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadIPv4AddressTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
loadPPortTableElementAddress '?'（Key signature）
  stack：[table_address, table_key(value or address)] ==> [element address]
--------------------------------------------------------------------------------

(5)object型的function result
注：2001/7/17这些指令被Discarded了!
--------------------------------------------------------------------------------
convertValueToAddress 'signature-of-string'
  注：如果某个function的返回是string等object型，则在function后必须将result argument
      转化为一个temp address，这样才符合ZVM中object型的运算规定。
      可能在ZVM中有这样一个特殊寄存器：
          struct TZVMStringRegister {
            CZVMString * pciString;

            TZVMStringRegister()
              : pciString(0)
            { }

            ~TZVMStringRegister()
            { delete pciString; }

            void Replace(CZVMString * pciNeedStoredString)
            {
              delete pciString;
              pciString = pciNeedStoredString;
            }
          };
      然后转换时先pop出那个CSlot，然后再
          TZVMStringRegister.Replace(CSlot.pciString)
      最后再
          push(CSlot(&(TZVMStringRegister.pciString))
      并标识为SLOT_TAG_ADDRESS_OF_STRING_OBJECT即可.

convertValueToAddress 'signature-of-rope'
convertValueToAddress 'signature-of-ipv4address'
convertValueToAddress 'signature-of-pport'
convertValueToAddress 'signature-of-table'
--------------------------------------------------------------------------------


六、取Constant值和地址指令
    何时采用value、何时采用address呢？
    (1)当ZVM的操作符需要的是value时，就采用value形式；当ZVM的操作符需要的是
       address时，就采用address形式.
    (2)当向function传递value argument时，就采用value形式.
    (3)当向function传递reference argument时，现在还不支持constant element被作为
       reference argument.

(1)load constant value
--------------------------------------------------------------------------------
loadConstantValue 'signature-of-bool' 0或1(1 byte)
loadConstantValue 'signature-of-byte' UCHAR(1 byte)
loadConstantValue 'signature-of-sdword' sdword(4 byte)
  注：对于sdword型，由于其占用的字节数与TZVMIndex一样，因此可直接将sdword-literal
      作为指令操作数，而不再使用index到constant pool去查询了.
loadConstantValue 'signature-of-udword' udword(4 byte)
  注：对于udword型，由于其占用的字节数与TZVMIndex一样，因此可直接将udword-literal
      作为指令操作数，而不再使用index到constant pool去查询了.
loadConstantValue 'signature-of-sqword' index(TZVMIndex)
loadConstantValue 'signature-of-uqword' index(TZVMIndex)
loadConstantValue 'signature-of-double' index(TZVMIndex)
loadConstantValue 'signature-of-string' index(TZVMIndex)
loadConstantValue 'signature-of-rope' index(TZVMIndex)
loadConstantValue 'signature-of-ipv4address' index(TZVMIndex)
loadConstantValue 'signature-of-pport' index(TZVMIndex)
--------------------------------------------------------------------------------

(2)load constant address
--------------------------------------------------------------------------------
loadConstantAddress 'signature-of-bool' 0或1
loadConstantAddress 'signature-of-byte' UCHAR(1 byte)
loadConstantAddress 'signature-of-sdword' sdword
loadConstantAddress 'signature-of-udword' udword
loadConstantAddress 'signature-of-sqword' sdword
loadConstantAddress 'signature-of-uqword' udword
loadConstantAddress 'signature-of-double' index
  注：上面的七条指令只是先保留着，现在还不打算支持.

loadConstantAddress 'signature-of-string' index
loadConstantAddress 'signature-of-rope' index
loadConstantAddress 'signature-of-ipv4address' index
loadConstantAddress 'signature-of-pport' index
  注：上面的三条指令目前还不允许用于reference argument.
--------------------------------------------------------------------------------


七、assign操作符
    assign操作符将产生store指令。基本上所有的store指令都有一个操作数来指明"目的"，
只有当存贮到table element时，才使用没有操作数的store指令，此时"目的element"的地址
在stack上被指明了.
注：store指令都采用deep copy方式，因此如果操作数是object型，则也是deep copy content.

(1)store value to global variable
--------------------------------------------------------------------------------
storeToGlobalVariable 'signature-of-bool' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-byte' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-sdword' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-udword' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-sqword' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-uqword' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-double' variable_index
  stack: [value] ==> []
storeToGlobalVariable 'signature-of-string' variable_index
  stack: [address] ==> []
  注：string是object，所以在stack顶上的右值是一个address
storeToGlobalVariable 'signature-of-rope' variable_index
  stack: [address] ==> []
  注：rope是object，所以在stack顶上的右值是一个address
storeToGlobalVariable 'signature-of-ipv4address' variable_index
  stack: [address] ==> []
  注：ipv4address是object，所以在stack顶上的右值是一个address
storeToGlobalVariable 'signature-of-pport' variable_index
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
storeToGlobalVariable 'signature-of-pport' variable_index
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
storeToGlobalVariable 'signature-of-table-prefix' variable_index
  stack: [address] ==> []
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(2)store value to local variable和value argument
--------------------------------------------------------------------------------
storeToStackVariable 'signature-of-bool' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-byte' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-sdword' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-udword' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-sqword' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-uqword' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-double' bp_offset
  stack: [value] ==> []
storeToStackVariable 'signature-of-string' bp_offset
  stack: [address] ==> []
  注：string是object，所以在stack顶上的右值是一个address
storeToStackVariable 'signature-of-rope' bp_offset
  stack: [address] ==> []
  注：rope是object，所以在stack顶上的右值是一个address
storeToStackVariable 'signature-of-ipv4address' bp_offset
  stack: [address] ==> []
  注：ipv4address是object，所以在stack顶上的右值是一个address
storeToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
storeToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
storeToStackVariable 'signature-of-table-prefix' bp_offset
  stack: [address] ==> []
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(3)store value to local reference variable和reference argument
--------------------------------------------------------------------------------
indirectStoreToStackVariable 'signature-of-bool' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-byte' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-sdword' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-udword' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-sqword' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-uqword' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-double' bp_offset
  stack: [value] ==> []
indirectStoreToStackVariable 'signature-of-string' bp_offset
  stack: [address] ==> []
  注：string是object，所以在stack顶上的右值是一个address
indirectStoreToStackVariable 'signature-of-rope' bp_offset
  stack: [address] ==> []
  注：rope是object，所以在stack顶上的右值是一个address
indirectStoreToStackVariable 'signature-of-ipv4address' bp_offset
  stack: [address] ==> []
  注：ipv4address是object，所以在stack顶上的右值是一个address
indirectStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
indirectStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
indirectStoreToStackVariable 'signature-of-table-prefix' bp_offset
  stack: [address] ==> []
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(4)store value to table element
注：在store to table element指令的前面一定有几条类似如下的指令：
        "load address of table"
        "load value or address of table key"
        "load ? table element address by ? key"
        "load value or address of source variable"
--------------------------------------------------------------------------------
storeToAddress 'signature-of-bool'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-byte'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-sdword'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-udword'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-sqword'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-uqword'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-double'
  stack: [table-element-address, value] ==> []
storeToAddress 'signature-of-string'
  stack: [table-element-address, address] ==> []
  注：string是object，所以在stack顶上的右值是一个address
storeToAddress 'signature-of-rope'
  stack: [table-element-address, address] ==> []
  注：rope是object，所以在stack顶上的右值是一个address
storeToAddress 'signature-of-ipv4address'
  stack: [table-element-address, address] ==> []
  注：ipv4address是object，所以在stack顶上的右值是一个address
storeToAddress 'signature-of-pport'
  stack: [table-element-address, address] ==> []
  注：pport是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(5)assign reference-to-address to local reference variable（reference argument不算）
--------------------------------------------------------------------------------
assignReferenceAddressToReferenceStackVariable 'signature-of-type'
  stack: [a-address] ==> []
  注：这些指令用于初始化reference stack variable引用到的Address.
--------------------------------------------------------------------------------


八、nested assign操作符
(1)store value to global variable
--------------------------------------------------------------------------------
nestedStoreToGlobalVariable 'signature-of-bool' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-byte' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-sdword' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-udword' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-sqword' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-uqword' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-double' variable_index
  stack: [value] ==> [value]
nestedStoreToGlobalVariable 'signature-of-string' variable_index
  stack: [address] ==> [address]
  注：string是object，所以在stack顶上的右值是一个address
nestedStoreToGlobalVariable 'signature-of-rope' variable_index
  stack: [address] ==> [address]
  注：rope是object，所以在stack顶上的右值是一个address
nestedStoreToGlobalVariable 'signature-of-ipv4address' variable_index
  stack: [address] ==> [address]
  注：ipv4address是object，所以在stack顶上的右值是一个address
nestedStoreToGlobalVariable 'signature-of-pport' variable_index
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
nestedStoreToGlobalVariable 'signature-of-pport' variable_index
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
nestedStoreToGlobalVariable 'signature-of-table-prefix' variable_index
  stack: [address] ==> [address]
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(2)store value to local variable和value argument
--------------------------------------------------------------------------------
nestedStoreToStackVariable 'signature-of-bool' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-byte' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-sdword' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-udword' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-sqword' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-uqword' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-double' bp_offset
  stack: [value] ==> [value]
nestedStoreToStackVariable 'signature-of-string' bp_offset
  stack: [address] ==> [address]
  注：string是object，所以在stack顶上的右值是一个address
nestedStoreToStackVariable 'signature-of-rope' bp_offset
  stack: [address] ==> [address]
  注：rope是object，所以在stack顶上的右值是一个address
nestedStoreToStackVariable 'signature-of-ipv4address' bp_offset
  stack: [address] ==> [address]
  注：ipv4address是object，所以在stack顶上的右值是一个address
nestedStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
nestedStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
nestedStoreToStackVariable 'signature-of-table-prefix' bp_offset
  stack: [address] ==> [address]
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(3)store value to local reference variable和reference argument
--------------------------------------------------------------------------------
indirectNestedStoreToStackVariable 'signature-of-bool' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-byte' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-sdword' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-udword' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-sqword' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-uqword' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-double' bp_offset
  stack: [value] ==> [value]
indirectNestedStoreToStackVariable 'signature-of-string' bp_offset
  stack: [address] ==> [address]
  注：string是object，所以在stack顶上的右值是一个address
indirectNestedStoreToStackVariable 'signature-of-rope' bp_offset
  stack: [address] ==> [address]
  注：rope是object，所以在stack顶上的右值是一个address
indirectNestedStoreToStackVariable 'signature-of-ipv4address' bp_offset
  stack: [address] ==> [address]
  注：ipv4address是object，所以在stack顶上的右值是一个address
indirectNestedStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
indirectNestedStoreToStackVariable 'signature-of-pport' bp_offset
  stack: [address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
indirectNestedStoreToStackVariable 'signature-of-table-prefix' bp_offset
  stack: [address] ==> [address]
  注：table是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------

(4)store value to table element
--------------------------------------------------------------------------------
nestedStoreToAddress 'signature-of-bool'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-byte'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-sdword'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-udword'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-sqword'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-uqword'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-double'
  stack: [table-element-address, value] ==> [value]
nestedStoreToAddress 'signature-of-string'
  stack: [table-element-address, address] ==> [address]
  注：string是object，所以在stack顶上的右值是一个address
nestedStoreToAddress 'signature-of-rope'
  stack: [table-element-address, address] ==> [address]
  注：rope是object，所以在stack顶上的右值是一个address
nestedStoreToAddress 'signature-of-ipv4address'
  stack: [table-element-address, address] ==> [address]
  注：ipv4address是object，所以在stack顶上的右值是一个address
nestedStoreToAddress 'signature-of-pport'
  stack: [table-element-address, address] ==> [address]
  注：pport是object，所以在stack顶上的右值是一个address
--------------------------------------------------------------------------------


九）算术、比较、cast指令
(1)二元指令
logicOr 'signature-char'
  弹出2个value或address，将它们进行逻辑or，再将结果一个新value或新address压入到stack顶.
logicAnd 'signature-char'
bitOr 'signature-char'
bitXor 'signature-char'
bitAnd 'signature-char'
notEqual 'signature-char'
equal 'signature-char'
less 'signature-char'
great 'signature-char'
lessEqual 'signature-char'
greatEqual 'signature-char'
shiftLeft 'signature-char'
  弹出一个'signature-char'型的value1和一个udword型value2，然后tmp=value1<<value2，
  再将tmp压入stack中.
shiftRight 'signature-char'
  弹出一个'signature-char'型的value1和一个udword型value2，然后tmp=value1>>value2，
  再将tmp压入stack中.
plus 'signature-char'
  注：2001/7/17: 对于string plus，则还需要一个指令操作数来指定plus的结果存贮到哪个临时变量中.
  注：2001/8/10: 对于rope plus，则还需要一个指令操作数来指定plus的结果存贮到哪个临时变量中.
minus 'signature-char'
multi 'signature-char'
div 'signature-char'
mod 'signature-char'

(2)一元指令
inc 'signature-char'
  弹出一个address，进行++prefix，然后再将结果一个新value压入到stack顶.
  注：操作数必须是简单类型数值变量.
dec 'signature-char'
  弹出一个address，进行--prefix，然后再将结果一个新value压入到stack顶.
  注：操作数必须是简单类型数值变量.
postInc 'signature-char'
  弹出一个address，进行postfix++，然后再将结果一个新value压入到stack顶.
  注：操作数必须是简单类型数值变量.
postDec 'signature-char'
  弹出一个address，进行postfix--，然后再将结果一个新value压入到stack顶.
  注：操作数必须是简单类型数值变量.
unaryPlus 'signature-char'
  弹出一个value，进行unaryPlus，然后再将结果一个新value压入到stack顶.
unaryMinus 'signature-char'
  弹出一个value，进行unaryMinus，然后再将结果一个新value压入到stack顶.
bitNot 'signature-char'
  弹出一个value，进行bNot，然后再将结果一个新value压入到stack顶.
logicNot 'signature-char'
  弹出一个value，进行lNot，然后再将结果一个新value压入到stack顶.

(3)cast指令
boolToByte
  弹出一个value，将其cast为byte，然后再将结果压入到stack顶.
boolToSDWORD
boolToUDWORD
boolToSQWORD
boolToUQWORD

byteToBool
byteToSDWORD
byteToUDWORD
byteToSQWORD
byteToUQWORD
byteToDouble

sdwordToBool
sdwordToByte
sdwordToUDWORD
sdwordToSQWORD
sdwordToUQWORD
sdwordToDouble

udwordToBool
udwordToByte
udwordToSDWORD
udwordToSQWORD
udwordToUQWORD
udwordToDouble

sqwordToBool
sqwordToByte
sqwordToSDWORD
sqwordToUDWORD
sqwordToUQWORD
sqwordToDouble

uqwordToBool
uqwordToByte
uqwordToSDWORD
uqwordToUDWORD
uqwordToSQWORD
uqwordToDouble

doubleToByte
doubleToSDWORD
doubleToUDWORD
doubleToSQWORD
doubleToUQWORD


十、Stack操作指令
(1)pop
pop 'signature-of-simple-type'
  弹出一个简单类型
pop 'signature-of-string'
  弹出一个string型，并做内存析构
pop 'signature-of-rope'
  弹出一个rope型，并做内存析构
pop 'signature-of-ipv4address'
  弹出一个ipv4address型，并做内存析构
pop 'signature-of-pport'
  弹出一个pport型，并做内存析构
pop 'signature-of-table'
  弹出一个table型，并做内存析构

(2)ret
    从stack顶不断地弹出一个个element，可能需同时对该element做一些内存析构工作。
如果弹出的element是saved-BP则恢复BP的值；直至弹出saved-PC为止，则停止pop，恢复
PC并跳转到PC指示指令处.

(3)pushBP
    将BP寄存器的值压入stack顶，同时还将push完成后当前的SP寄存器值存储到BP寄存器中.

(4)construct 'signature-char'
    在stack顶上construct一个相应类型的stack variable.

(5)constructTable 'signature-char'
    在stack顶上construct一个相应类型的table型stack variable.

(6)constructReference 'signature-char'
    在stack顶上construct一个相应类型的reference型stack variable.

(7)quickConstructObject 'object-type-signature-char' temp_variable_bp_offset
    在stack顶上construct一个相应(Object)类型的stack variable，但是这个
object variable的内存却是直接从某个temp object stack variable借来的，即
它可以被看作是那个temp object stack variable的shadow.


十一、PC转移操作
(1)falseJump 'signature-char' code_label_offset(SDWORD)
    从stack顶弹出一个'signature-char'型element，然后判断其为false否再跳转，此时
的跳转是将falseJump跟随的操作数code_label_offset加到PC上，然后这样PC就自然实现了
转移.
注：code_label_offset的数据类型是TZVMIndex，即必须将code_label_offset作为有符号
    数来处理，这样才能实现PC的向前跳转.
注：采用offset而不是直接的code_label的原因是：因为在我的ZVM的实现中，PC寄存器被
    设计为一个代码流指针，因此直接的code_label是没法使用的.

(2)unlimitJump code_label_offset(SDWORD)
    无条件地跳转到指定的code_label处，此时的跳转是将unlimitJump跟随的操作数
code_label_offset加到PC上，然后这样PC就自然实现了转移.

(3)call function_index
    将PC转到function_index所指的function的开始代码处.

(4)falseCircuitJump 'signature-char' code_label_offset(SDWORD)
    检测stack顶上的那个'signature-char'型element，判断其为false否再决定是否
进行Logic AND短路跳转，短路跳转前要先将原来ZVM stack顶的那个element偷改为bool
型false值，然后再调整PC寄存器.

(5)trueCircuitJump 'signature-char' code_label_offset(SDWORD)
    检测stack顶上的那个'signature-char'型element，判断其为true否再决定是否
进行Logic OR短路跳转，短路跳转前要先将原来ZVM stack顶的那个element偷改为bool
型true值，然后再调整PC寄存器.

</pre>

*/


/**
 * @name 取值指令
 */
//@{
const TZVMICode ZVM_loadGlobalVariableValue = 0x0100;
const TZVMICode ZVM_loadBoolGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_loadTableGlobalVariableValue = (ZVM_loadGlobalVariableValue | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_loadStackVariableValue = 0x0200;
const TZVMICode ZVM_loadBoolStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_loadTableStackVariableValue = (ZVM_loadStackVariableValue | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_indirectLoadStackVariableValue = 0x0300;
const TZVMICode ZVM_indirectLoadBoolStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_indirectLoadByteStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_indirectLoadSDWORDStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectLoadUDWORDStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectLoadSQWORDStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectLoadUQWORDStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectLoadDoubleStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_indirectLoadStringStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_indirectLoadRopeStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_indirectLoadIPv4AddressStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_indirectLoadPPortStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_indirectLoadTableStackVariableValue = (ZVM_indirectLoadStackVariableValue | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_loadBoolTableElementValue = 0x0400;
const TZVMICode ZVM_loadBoolTableElementValueByBoolKey = (ZVM_loadBoolTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByByteKey = (ZVM_loadBoolTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueBySDWORDKey = (ZVM_loadBoolTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByUDWORDKey = (ZVM_loadBoolTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueBySQWORDKey = (ZVM_loadBoolTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByUQWORDKey = (ZVM_loadBoolTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByDoubleKey = (ZVM_loadBoolTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByStringKey = (ZVM_loadBoolTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByRopeKey = (ZVM_loadBoolTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByIPv4AddressKey = (ZVM_loadBoolTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementValueByPPortKey = (ZVM_loadBoolTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadByteTableElementValue = 0x0500;
const TZVMICode ZVM_loadByteTableElementValueByBoolKey = (ZVM_loadByteTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByByteKey = (ZVM_loadByteTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueBySDWORDKey = (ZVM_loadByteTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByUDWORDKey = (ZVM_loadByteTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueBySQWORDKey = (ZVM_loadByteTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByUQWORDKey = (ZVM_loadByteTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByDoubleKey = (ZVM_loadByteTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByStringKey = (ZVM_loadByteTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByRopeKey = (ZVM_loadByteTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByIPv4AddressKey = (ZVM_loadByteTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementValueByPPortKey = (ZVM_loadByteTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadSDWORDTableElementValue = 0x0600;
const TZVMICode ZVM_loadSDWORDTableElementValueByBoolKey = (ZVM_loadSDWORDTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByByteKey = (ZVM_loadSDWORDTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueBySDWORDKey = (ZVM_loadSDWORDTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByUDWORDKey = (ZVM_loadSDWORDTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueBySQWORDKey = (ZVM_loadSDWORDTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByUQWORDKey = (ZVM_loadSDWORDTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByDoubleKey = (ZVM_loadSDWORDTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByStringKey = (ZVM_loadSDWORDTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByRopeKey = (ZVM_loadSDWORDTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByIPv4AddressKey = (ZVM_loadSDWORDTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementValueByPPortKey = (ZVM_loadSDWORDTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadUDWORDTableElementValue = 0x0700;
const TZVMICode ZVM_loadUDWORDTableElementValueByBoolKey = (ZVM_loadUDWORDTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByByteKey = (ZVM_loadUDWORDTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueBySDWORDKey = (ZVM_loadUDWORDTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByUDWORDKey = (ZVM_loadUDWORDTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueBySQWORDKey = (ZVM_loadUDWORDTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByUQWORDKey = (ZVM_loadUDWORDTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByDoubleKey = (ZVM_loadUDWORDTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByStringKey = (ZVM_loadUDWORDTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByRopeKey = (ZVM_loadUDWORDTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByIPv4AddressKey = (ZVM_loadUDWORDTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementValueByPPortKey = (ZVM_loadUDWORDTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadSQWORDTableElementValue = 0x0800;
const TZVMICode ZVM_loadSQWORDTableElementValueByBoolKey = (ZVM_loadSQWORDTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByByteKey = (ZVM_loadSQWORDTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueBySDWORDKey = (ZVM_loadSQWORDTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByUDWORDKey = (ZVM_loadSQWORDTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueBySQWORDKey = (ZVM_loadSQWORDTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByUQWORDKey = (ZVM_loadSQWORDTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByDoubleKey = (ZVM_loadSQWORDTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByStringKey = (ZVM_loadSQWORDTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByRopeKey = (ZVM_loadSQWORDTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByIPv4AddressKey = (ZVM_loadSQWORDTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementValueByPPortKey = (ZVM_loadSQWORDTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadUQWORDTableElementValue = 0x0900;
const TZVMICode ZVM_loadUQWORDTableElementValueByBoolKey = (ZVM_loadUQWORDTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByByteKey = (ZVM_loadUQWORDTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueBySDWORDKey = (ZVM_loadUQWORDTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByUDWORDKey = (ZVM_loadUQWORDTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueBySQWORDKey = (ZVM_loadUQWORDTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByUQWORDKey = (ZVM_loadUQWORDTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByDoubleKey = (ZVM_loadUQWORDTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByStringKey = (ZVM_loadUQWORDTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByRopeKey = (ZVM_loadUQWORDTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByIPv4AddressKey = (ZVM_loadUQWORDTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementValueByPPortKey = (ZVM_loadUQWORDTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadDoubleTableElementValue = 0x0A00;
const TZVMICode ZVM_loadDoubleTableElementValueByBoolKey = (ZVM_loadDoubleTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByByteKey = (ZVM_loadDoubleTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueBySDWORDKey = (ZVM_loadDoubleTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByUDWORDKey = (ZVM_loadDoubleTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueBySQWORDKey = (ZVM_loadDoubleTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByUQWORDKey = (ZVM_loadDoubleTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByDoubleKey = (ZVM_loadDoubleTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByStringKey = (ZVM_loadDoubleTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByRopeKey = (ZVM_loadDoubleTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByIPv4AddressKey = (ZVM_loadDoubleTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementValueByPPortKey = (ZVM_loadDoubleTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadStringTableElementValue = 0x0B00;
const TZVMICode ZVM_loadStringTableElementValueByBoolKey = (ZVM_loadStringTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByByteKey = (ZVM_loadStringTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueBySDWORDKey = (ZVM_loadStringTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByUDWORDKey = (ZVM_loadStringTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueBySQWORDKey = (ZVM_loadStringTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByUQWORDKey = (ZVM_loadStringTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByDoubleKey = (ZVM_loadStringTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByStringKey = (ZVM_loadStringTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByRopeKey = (ZVM_loadStringTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByIPv4AddressKey = (ZVM_loadStringTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementValueByPPortKey = (ZVM_loadStringTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadRopeTableElementValue = 0x0C00;
const TZVMICode ZVM_loadRopeTableElementValueByBoolKey = (ZVM_loadRopeTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByByteKey = (ZVM_loadRopeTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueBySDWORDKey = (ZVM_loadRopeTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByUDWORDKey = (ZVM_loadRopeTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueBySQWORDKey = (ZVM_loadRopeTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByUQWORDKey = (ZVM_loadRopeTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByDoubleKey = (ZVM_loadRopeTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByStringKey = (ZVM_loadRopeTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByRopeKey = (ZVM_loadRopeTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByIPv4AddressKey = (ZVM_loadRopeTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementValueByPPortKey = (ZVM_loadRopeTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadIPv4AddressTableElementValue = 0x0D00;
const TZVMICode ZVM_loadIPv4AddressTableElementValueByBoolKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByByteKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueBySDWORDKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByUDWORDKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueBySQWORDKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByUQWORDKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByDoubleKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByStringKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByRopeKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByIPv4AddressKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementValueByPPortKey = (ZVM_loadIPv4AddressTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadPPortTableElementValue = 0x0E00;
const TZVMICode ZVM_loadPPortTableElementValueByBoolKey = (ZVM_loadPPortTableElementValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByByteKey = (ZVM_loadPPortTableElementValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueBySDWORDKey = (ZVM_loadPPortTableElementValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByUDWORDKey = (ZVM_loadPPortTableElementValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueBySQWORDKey = (ZVM_loadPPortTableElementValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByUQWORDKey = (ZVM_loadPPortTableElementValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByDoubleKey = (ZVM_loadPPortTableElementValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByStringKey = (ZVM_loadPPortTableElementValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByRopeKey = (ZVM_loadPPortTableElementValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByIPv4AddressKey = (ZVM_loadPPortTableElementValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementValueByPPortKey = (ZVM_loadPPortTableElementValue | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_indirectLoadValueFromAddress = 0x0F00;
const TZVMICode ZVM_indirectLoadStringValueFromAddress = (ZVM_indirectLoadValueFromAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_indirectLoadRopeValueFromAddress = (ZVM_indirectLoadValueFromAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_indirectLoadIPv4AddressValueFromAddress = (ZVM_indirectLoadValueFromAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_indirectLoadPPortValueFromAddress = (ZVM_indirectLoadValueFromAddress | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_indirectLoadTableValueFromAddress = (ZVM_indirectLoadValueFromAddress | CchZVM_TABLE_TYPE_TAG);
//@}

/**
 * @name 取地址指令
 */
//@{
const TZVMICode ZVM_loadGlobalVariableAddress = 0x1000;
const TZVMICode ZVM_loadBoolGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_loadTableGlobalVariableAddress = (ZVM_loadGlobalVariableAddress | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_loadStackVariableAddress = 0x1100;
const TZVMICode ZVM_loadBoolStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_loadTableStackVariableAddress = (ZVM_loadStackVariableAddress | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_loadReferenceStackVariableReferenceToAddress = 0x1200 | CchZVM_VOID_TYPE_TAG;

const TZVMICode ZVM_loadBoolTableElementAddress = 0x1300;
const TZVMICode ZVM_loadBoolTableElementAddressByBoolKey = (ZVM_loadBoolTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByByteKey = (ZVM_loadBoolTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressBySDWORDKey = (ZVM_loadBoolTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByUDWORDKey = (ZVM_loadBoolTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressBySQWORDKey = (ZVM_loadBoolTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByUQWORDKey = (ZVM_loadBoolTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByDoubleKey = (ZVM_loadBoolTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByStringKey = (ZVM_loadBoolTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByRopeKey = (ZVM_loadBoolTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByIPv4AddressKey = (ZVM_loadBoolTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadBoolTableElementAddressByPPortKey = (ZVM_loadBoolTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadByteTableElementAddress = 0x1400;
const TZVMICode ZVM_loadByteTableElementAddressByBoolKey = (ZVM_loadByteTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByByteKey = (ZVM_loadByteTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressBySDWORDKey = (ZVM_loadByteTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByUDWORDKey = (ZVM_loadByteTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressBySQWORDKey = (ZVM_loadByteTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByUQWORDKey = (ZVM_loadByteTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByDoubleKey = (ZVM_loadByteTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByStringKey = (ZVM_loadByteTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByRopeKey = (ZVM_loadByteTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByIPv4AddressKey = (ZVM_loadByteTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadByteTableElementAddressByPPortKey = (ZVM_loadByteTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadSDWORDTableElementAddress = 0x1500;
const TZVMICode ZVM_loadSDWORDTableElementAddressByBoolKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByByteKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressBySDWORDKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByUDWORDKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressBySQWORDKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByUQWORDKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByDoubleKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByStringKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByRopeKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByIPv4AddressKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDTableElementAddressByPPortKey = (ZVM_loadSDWORDTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadUDWORDTableElementAddress = 0x1600;
const TZVMICode ZVM_loadUDWORDTableElementAddressByBoolKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByByteKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressBySDWORDKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByUDWORDKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressBySQWORDKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByUQWORDKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByDoubleKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByStringKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByRopeKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByIPv4AddressKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDTableElementAddressByPPortKey = (ZVM_loadUDWORDTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadSQWORDTableElementAddress = 0x1700;
const TZVMICode ZVM_loadSQWORDTableElementAddressByBoolKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByByteKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressBySDWORDKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByUDWORDKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressBySQWORDKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByUQWORDKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByDoubleKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByStringKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByRopeKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByIPv4AddressKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDTableElementAddressByPPortKey = (ZVM_loadSQWORDTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadUQWORDTableElementAddress = 0x1800;
const TZVMICode ZVM_loadUQWORDTableElementAddressByBoolKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByByteKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressBySDWORDKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByUDWORDKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressBySQWORDKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByUQWORDKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByDoubleKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByStringKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByRopeKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByIPv4AddressKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDTableElementAddressByPPortKey = (ZVM_loadUQWORDTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadDoubleTableElementAddress = 0x1900;
const TZVMICode ZVM_loadDoubleTableElementAddressByBoolKey = (ZVM_loadDoubleTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByByteKey = (ZVM_loadDoubleTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressBySDWORDKey = (ZVM_loadDoubleTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByUDWORDKey = (ZVM_loadDoubleTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressBySQWORDKey = (ZVM_loadDoubleTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByUQWORDKey = (ZVM_loadDoubleTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByDoubleKey = (ZVM_loadDoubleTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByStringKey = (ZVM_loadDoubleTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByRopeKey = (ZVM_loadDoubleTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByIPv4AddressKey = (ZVM_loadDoubleTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadDoubleTableElementAddressByPPortKey = (ZVM_loadDoubleTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadStringTableElementAddress = 0x2000;
const TZVMICode ZVM_loadStringTableElementAddressByBoolKey = (ZVM_loadStringTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByByteKey = (ZVM_loadStringTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressBySDWORDKey = (ZVM_loadStringTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByUDWORDKey = (ZVM_loadStringTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressBySQWORDKey = (ZVM_loadStringTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByUQWORDKey = (ZVM_loadStringTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByDoubleKey = (ZVM_loadStringTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByStringKey = (ZVM_loadStringTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByRopeKey = (ZVM_loadStringTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByIPv4AddressKey = (ZVM_loadStringTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadStringTableElementAddressByPPortKey = (ZVM_loadStringTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadRopeTableElementAddress = 0x2100;
const TZVMICode ZVM_loadRopeTableElementAddressByBoolKey = (ZVM_loadRopeTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByByteKey = (ZVM_loadRopeTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressBySDWORDKey = (ZVM_loadRopeTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByUDWORDKey = (ZVM_loadRopeTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressBySQWORDKey = (ZVM_loadRopeTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByUQWORDKey = (ZVM_loadRopeTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByDoubleKey = (ZVM_loadRopeTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByStringKey = (ZVM_loadRopeTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByRopeKey = (ZVM_loadRopeTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByIPv4AddressKey = (ZVM_loadRopeTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadRopeTableElementAddressByPPortKey = (ZVM_loadRopeTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadIPv4AddressTableElementAddress = 0x2200;
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByBoolKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByByteKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressBySDWORDKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByUDWORDKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressBySQWORDKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByUQWORDKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByDoubleKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByStringKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByRopeKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByIPv4AddressKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressTableElementAddressByPPortKey = (ZVM_loadIPv4AddressTableElementAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_loadPPortTableElementAddress = 0x2300;
const TZVMICode ZVM_loadPPortTableElementAddressByBoolKey = (ZVM_loadPPortTableElementAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByByteKey = (ZVM_loadPPortTableElementAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressBySDWORDKey = (ZVM_loadPPortTableElementAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByUDWORDKey = (ZVM_loadPPortTableElementAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressBySQWORDKey = (ZVM_loadPPortTableElementAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByUQWORDKey = (ZVM_loadPPortTableElementAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByDoubleKey = (ZVM_loadPPortTableElementAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByStringKey = (ZVM_loadPPortTableElementAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByRopeKey = (ZVM_loadPPortTableElementAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByIPv4AddressKey = (ZVM_loadPPortTableElementAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortTableElementAddressByPPortKey = (ZVM_loadPPortTableElementAddress | CchZVM_PPORT_TYPE_TAG);

/* 2001/7/17: Discarded
const TZVMICode ZVM_convertValueToAddress = 0x2400;
const TZVMICode ZVM_convertStringValueToAddress = (ZVM_convertValueToAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_convertRopeValueToAddress = (ZVM_convertValueToAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_convertIPv4AddressValueToAddress = (ZVM_convertValueToAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_convertPPortValueToAddress = (ZVM_convertValueToAddress | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_convertTableValueToAddress = (ZVM_convertValueToAddress | CchZVM_TABLE_TYPE_TAG);
*/
//@}

/**
 * @name 取Constant值指令
 */
//@{
const TZVMICode ZVM_loadConstantValue = 0x2800;
const TZVMICode ZVM_loadBoolConstantValue = (ZVM_loadConstantValue | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_loadByteConstantValue = (ZVM_loadConstantValue | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_loadSDWORDConstantValue = (ZVM_loadConstantValue | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_loadUDWORDConstantValue = (ZVM_loadConstantValue | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_loadSQWORDConstantValue = (ZVM_loadConstantValue | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_loadUQWORDConstantValue = (ZVM_loadConstantValue | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_loadDoubleConstantValue = (ZVM_loadConstantValue | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringConstantValue = (ZVM_loadConstantValue | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeConstantValue = (ZVM_loadConstantValue | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressConstantValue = (ZVM_loadConstantValue | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortConstantValue = (ZVM_loadConstantValue | CchZVM_PPORT_TYPE_TAG);
//@}

/**
 * @name 取Constant地址指令
 */
//@{
const TZVMICode ZVM_loadConstantAddress = 0x2900;
//const TZVMICode ZVM_loadBoolConstantAddress = (ZVM_loadConstantAddress | CchZVM_BOOL_TYPE_TAG);
//const TZVMICode ZVM_loadByteConstantAddress = (ZVM_loadConstantAddress | CchZVM_BYTE_TYPE_TAG);
//const TZVMICode ZVM_loadSDWORDConstantAddress = (ZVM_loadConstantAddress | CchZVM_SDWORD_TYPE_TAG);
//const TZVMICode ZVM_loadUDWORDConstantAddress = (ZVM_loadConstantAddress | CchZVM_UDWORD_TYPE_TAG);
//const TZVMICode ZVM_loadSQWORDConstantAddress = (ZVM_loadConstantAddress | CchZVM_SQWORD_TYPE_TAG);
//const TZVMICode ZVM_loadUQWORDConstantAddress = (ZVM_loadConstantAddress | CchZVM_UQWORD_TYPE_TAG);
//const TZVMICode ZVM_loadDoubleConstantAddress = (ZVM_loadConstantAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_loadStringConstantAddress = (ZVM_loadConstantAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_loadRopeConstantAddress = (ZVM_loadConstantAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_loadIPv4AddressConstantAddress = (ZVM_loadConstantAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_loadPPortConstantAddress = (ZVM_loadConstantAddress | CchZVM_PPORT_TYPE_TAG);
//@}

/**
 * @name 非嵌套型的存贮值指令
 */
//@{
const TZVMICode ZVM_storeToGlobalVariable = 0x2F00;
const TZVMICode ZVM_storeToBoolGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_storeToByteGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_storeToSDWORDGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_storeToUDWORDGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_storeToSQWORDGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_storeToUQWORDGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_storeToDoubleGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_storeToStringGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_storeToRopeGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_storeToIPv4AddressGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_storeToPPortGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_storeToTableGlobalVariable = (ZVM_storeToGlobalVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_storeToStackVariable = 0x3000;
const TZVMICode ZVM_storeToBoolStackVariable = (ZVM_storeToStackVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_storeToByteStackVariable = (ZVM_storeToStackVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_storeToSDWORDStackVariable = (ZVM_storeToStackVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_storeToUDWORDStackVariable = (ZVM_storeToStackVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_storeToSQWORDStackVariable = (ZVM_storeToStackVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_storeToUQWORDStackVariable = (ZVM_storeToStackVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_storeToDoubleStackVariable = (ZVM_storeToStackVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_storeToStringStackVariable = (ZVM_storeToStackVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_storeToRopeStackVariable = (ZVM_storeToStackVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_storeToIPv4AddressStackVariable = (ZVM_storeToStackVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_storeToPPortStackVariable = (ZVM_storeToStackVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_storeToTableStackVariable = (ZVM_storeToStackVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_indirectStoreToStackVariable = 0x3100;
const TZVMICode ZVM_indirectStoreToBoolStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToByteStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToSDWORDStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToUDWORDStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToSQWORDStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToUQWORDStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToDoubleStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToStringStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToRopeStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToIPv4AddressStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToPPortStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_indirectStoreToTableStackVariable = (ZVM_indirectStoreToStackVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_storeToAddress = 0x3200;
const TZVMICode ZVM_storeBoolToAddress = (ZVM_storeToAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_storeByteToAddress = (ZVM_storeToAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_storeSDWORDToAddress = (ZVM_storeToAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_storeUDWORDToAddress = (ZVM_storeToAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_storeSQWORDToAddress = (ZVM_storeToAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_storeUQWORDToAddress = (ZVM_storeToAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_storeDoubleToAddress = (ZVM_storeToAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_storeStringToAddress = (ZVM_storeToAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_storeRopeToAddress = (ZVM_storeToAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_storeIPv4AddressToAddress = (ZVM_storeToAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_storePPortToAddress = (ZVM_storeToAddress | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_assignReferenceAddress = 0x3300;
const TZVMICode ZVM_assignReferenceAddressToBoolReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToByteReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToSDWORDReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToUDWORDReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToSQWORDReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToUQWORDReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToDoubleReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToStringReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToRopeReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToIPv4AddressReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToPPortReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_assignReferenceAddressToTableReferenceStackVariable = (ZVM_assignReferenceAddress | CchZVM_TABLE_TYPE_TAG);
//@}

/**
 * @name 嵌套型的存贮值指令
 */
//@{
const TZVMICode ZVM_nestedStoreToGlobalVariable = 0x3400;
const TZVMICode ZVM_nestedStoreToBoolGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToByteGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToSDWORDGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToUDWORDGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToSQWORDGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToUQWORDGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToDoubleGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToStringGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToRopeGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToIPv4AddressGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToPPortGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToTableGlobalVariable = (ZVM_nestedStoreToGlobalVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_nestedStoreToStackVariable = 0x3500;
const TZVMICode ZVM_nestedStoreToBoolStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToByteStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToSDWORDStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToUDWORDStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToSQWORDStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToUQWORDStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToDoubleStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToStringStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToRopeStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToIPv4AddressStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToPPortStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_nestedStoreToTableStackVariable = (ZVM_nestedStoreToStackVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_indirectNestedStoreToStackVariable = 0x3600;
const TZVMICode ZVM_indirectNestedStoreToBoolStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToByteStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToSDWORDStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToUDWORDStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToSQWORDStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToUQWORDStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToDoubleStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToStringStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToRopeStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToIPv4AddressStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToPPortStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_indirectNestedStoreToTableStackVariable = (ZVM_indirectNestedStoreToStackVariable | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_nestedStoreToAddress = 0x3700;
const TZVMICode ZVM_nestedStoreBoolToAddress = (ZVM_nestedStoreToAddress | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_nestedStoreByteToAddress = (ZVM_nestedStoreToAddress | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreSDWORDToAddress = (ZVM_nestedStoreToAddress | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreUDWORDToAddress = (ZVM_nestedStoreToAddress | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreSQWORDToAddress = (ZVM_nestedStoreToAddress | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreUQWORDToAddress = (ZVM_nestedStoreToAddress | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_nestedStoreDoubleToAddress = (ZVM_nestedStoreToAddress | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreStringToAddress = (ZVM_nestedStoreToAddress | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_nestedStoreRopeToAddress = (ZVM_nestedStoreToAddress | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_nestedStoreIPv4AddressToAddress = (ZVM_nestedStoreToAddress | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_nestedStorePPortToAddress = (ZVM_nestedStoreToAddress | CchZVM_PPORT_TYPE_TAG);
//@}

/**
 * @name 二元指令
 */
//@{
const TZVMICode ZVM_logicOr = 0x3800;
const TZVMICode ZVM_boolLogicOr = (ZVM_logicOr | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteLogicOr = (ZVM_logicOr | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordLogicOr = (ZVM_logicOr | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordLogicOr = (ZVM_logicOr | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordLogicOr = (ZVM_logicOr | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordLogicOr = (ZVM_logicOr | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleLogicOr = (ZVM_logicOr | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_logicAnd = 0x3900;
const TZVMICode ZVM_boolLogicAnd = (ZVM_logicAnd | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteLogicAnd = (ZVM_logicAnd | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordLogicAnd = (ZVM_logicAnd | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordLogicAnd = (ZVM_logicAnd | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordLogicAnd = (ZVM_logicAnd | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordLogicAnd = (ZVM_logicAnd | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleLogicAnd = (ZVM_logicAnd | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_bitOr = 0x4000;
const TZVMICode ZVM_byteBitOr = (ZVM_bitOr | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordBitOr = (ZVM_bitOr | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordBitOr = (ZVM_bitOr | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordBitOr = (ZVM_bitOr | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordBitOr = (ZVM_bitOr | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_bitXor = 0x4100;
const TZVMICode ZVM_byteBitXor = (ZVM_bitXor | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordBitXor = (ZVM_bitXor | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordBitXor = (ZVM_bitXor | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordBitXor = (ZVM_bitXor | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordBitXor = (ZVM_bitXor | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_bitAnd = 0x4200;
const TZVMICode ZVM_byteBitAnd = (ZVM_bitAnd | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordBitAnd = (ZVM_bitAnd | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordBitAnd = (ZVM_bitAnd | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordBitAnd = (ZVM_bitAnd | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordBitAnd = (ZVM_bitAnd | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_notEqual = 0x4300;
const TZVMICode ZVM_boolNotEqual = (ZVM_notEqual | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteNotEqual = (ZVM_notEqual | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordNotEqual = (ZVM_notEqual | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordNotEqual = (ZVM_notEqual | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordNotEqual = (ZVM_notEqual | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordNotEqual = (ZVM_notEqual | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleNotEqual = (ZVM_notEqual | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringNotEqual = (ZVM_notEqual | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeNotEqual = (ZVM_notEqual | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_ipv4addressNotEqual = (ZVM_notEqual | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_pportNotEqual = (ZVM_notEqual | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_equal = 0x4400;
const TZVMICode ZVM_boolEqual = (ZVM_equal | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteEqual = (ZVM_equal | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordEqual = (ZVM_equal | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordEqual = (ZVM_equal | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordEqual = (ZVM_equal | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordEqual = (ZVM_equal | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleEqual = (ZVM_equal | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringEqual = (ZVM_equal | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeEqual = (ZVM_equal | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_ipv4addressEqual = (ZVM_equal | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_pportEqual = (ZVM_equal | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_less = 0x4500;
const TZVMICode ZVM_byteLess = (ZVM_less | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordLess = (ZVM_less | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordLess = (ZVM_less | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordLess = (ZVM_less | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordLess = (ZVM_less | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleLess = (ZVM_less | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringLess = (ZVM_less | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeLess = (ZVM_less | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_pportLess = (ZVM_less | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_great = 0x4600;
const TZVMICode ZVM_byteGreat = (ZVM_great | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordGreat = (ZVM_great | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordGreat = (ZVM_great | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordGreat = (ZVM_great | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordGreat = (ZVM_great | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleGreat = (ZVM_great | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringGreat = (ZVM_great | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeGreat = (ZVM_great | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_pportGreat = (ZVM_great | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_lessEqual = 0x4700;
const TZVMICode ZVM_byteLessEqual = (ZVM_lessEqual | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordLessEqual = (ZVM_lessEqual | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordLessEqual = (ZVM_lessEqual | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordLessEqual = (ZVM_lessEqual | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordLessEqual = (ZVM_lessEqual | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleLessEqual = (ZVM_lessEqual | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringLessEqual = (ZVM_lessEqual | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeLessEqual = (ZVM_lessEqual | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_pportLessEqual = (ZVM_lessEqual | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_greatEqual = 0x4800;
const TZVMICode ZVM_byteGreatEqual = (ZVM_greatEqual | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordGreatEqual = (ZVM_greatEqual | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordGreatEqual = (ZVM_greatEqual | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordGreatEqual = (ZVM_greatEqual | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordGreatEqual = (ZVM_greatEqual | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleGreatEqual = (ZVM_greatEqual | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringGreatEqual = (ZVM_greatEqual | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeGreatEqual = (ZVM_greatEqual | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_pportGreatEqual = (ZVM_greatEqual | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_shiftLeft = 0x4900;
const TZVMICode ZVM_byteShiftLeft = (ZVM_shiftLeft | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordShiftLeft = (ZVM_shiftLeft | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordShiftLeft = (ZVM_shiftLeft | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordShiftLeft = (ZVM_shiftLeft | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordShiftLeft = (ZVM_shiftLeft | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_shiftRight = 0x5000;
const TZVMICode ZVM_byteShiftRight = (ZVM_shiftRight | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordShiftRight = (ZVM_shiftRight | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordShiftRight = (ZVM_shiftRight | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordShiftRight = (ZVM_shiftRight | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordShiftRight = (ZVM_shiftRight | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_plus = 0x5100;
const TZVMICode ZVM_bytePlus = (ZVM_plus | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordPlus = (ZVM_plus | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordPlus = (ZVM_plus | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordPlus = (ZVM_plus | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordPlus = (ZVM_plus | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doublePlus = (ZVM_plus | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringPlus = (ZVM_plus | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropePlus = (ZVM_plus | CchZVM_ROPE_TYPE_TAG);

const TZVMICode ZVM_minus = 0x5200;
const TZVMICode ZVM_byteMinus = (ZVM_minus | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordMinus = (ZVM_minus | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordMinus = (ZVM_minus | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordMinus = (ZVM_minus | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordMinus = (ZVM_minus | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleMinus = (ZVM_minus | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_multi = 0x5300;
const TZVMICode ZVM_byteMulti = (ZVM_multi | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordMulti = (ZVM_multi | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordMulti = (ZVM_multi | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordMulti = (ZVM_multi | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordMulti = (ZVM_multi | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleMulti = (ZVM_multi | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_div = 0x5400;
const TZVMICode ZVM_byteDiv = (ZVM_div | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordDiv = (ZVM_div | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordDiv = (ZVM_div | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordDiv = (ZVM_div | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordDiv = (ZVM_div | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleDiv = (ZVM_div | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_mod = 0x5500;
const TZVMICode ZVM_byteMod = (ZVM_mod | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordMod = (ZVM_mod | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordMod = (ZVM_mod | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordMod = (ZVM_mod | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordMod = (ZVM_mod | CchZVM_UQWORD_TYPE_TAG);
/* C/C++不允许"double % double"
const TZVMICode ZVM_doubleMod = (ZVM_mod | CchZVM_DOUBLE_TYPE_TAG);
*/
//@}

/**
 * @name 一元指令
 */
//@{
const TZVMICode ZVM_prefixInc = 0x5600;
const TZVMICode ZVM_bytePrefixInc = (ZVM_prefixInc | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordPrefixInc = (ZVM_prefixInc | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordPrefixInc = (ZVM_prefixInc | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordPrefixInc = (ZVM_prefixInc | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordPrefixInc = (ZVM_prefixInc | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doublePrefixInc = (ZVM_prefixInc | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_prefixDec = 0x5700;
const TZVMICode ZVM_bytePrefixDec = (ZVM_prefixDec | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordPrefixDec = (ZVM_prefixDec | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordPrefixDec = (ZVM_prefixDec | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordPrefixDec = (ZVM_prefixDec | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordPrefixDec = (ZVM_prefixDec | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doublePrefixDec = (ZVM_prefixDec | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_postfixInc = 0x5800;
const TZVMICode ZVM_bytePostfixInc = (ZVM_postfixInc | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordPostfixInc = (ZVM_postfixInc | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordPostfixInc = (ZVM_postfixInc | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordPostfixInc = (ZVM_postfixInc | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordPostfixInc = (ZVM_postfixInc | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doublePostfixInc = (ZVM_postfixInc | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_postfixDec = 0x5900;
const TZVMICode ZVM_bytePostfixDec = (ZVM_postfixDec | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordPostfixDec = (ZVM_postfixDec | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordPostfixDec = (ZVM_postfixDec | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordPostfixDec = (ZVM_postfixDec | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordPostfixDec = (ZVM_postfixDec | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doublePostfixDec = (ZVM_postfixDec | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_unaryPlus = 0x5A00;
const TZVMICode ZVM_byteUnaryPlus = (ZVM_unaryPlus | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordUnaryPlus = (ZVM_unaryPlus | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordUnaryPlus = (ZVM_unaryPlus | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordUnaryPlus = (ZVM_unaryPlus | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordUnaryPlus = (ZVM_unaryPlus | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleUnaryPlus = (ZVM_unaryPlus | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_unaryMinus = 0x5B00;
const TZVMICode ZVM_byteUnaryMinus = (ZVM_unaryMinus | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordUnaryMinus = (ZVM_unaryMinus | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordUnaryMinus = (ZVM_unaryMinus | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordUnaryMinus = (ZVM_unaryMinus | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordUnaryMinus = (ZVM_unaryMinus | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleUnaryMinus = (ZVM_unaryMinus | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_bitNot = 0x5C00;
const TZVMICode ZVM_byteBitNot = (ZVM_bitNot | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordBitNot = (ZVM_bitNot | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordBitNot = (ZVM_bitNot | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordBitNot = (ZVM_bitNot | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordBitNot = (ZVM_bitNot | CchZVM_UQWORD_TYPE_TAG);
/* C/C++不允许"~double"
const TZVMICode ZVM_doubleBitNot = (ZVM_bitNot | CchZVM_DOUBLE_TYPE_TAG);
*/

const TZVMICode ZVM_logicNot = 0x5D00;
const TZVMICode ZVM_boolLogicNot = (ZVM_logicNot | CchZVM_BOOL_TYPE_TAG);
//@}

/**
 * @name cast指令
 */
//@{
const TZVMICode ZVM_boolTo = 0x5E00;
const TZVMICode ZVM_boolToByte = (ZVM_boolTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_boolToSDWORD = (ZVM_boolTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_boolToUDWORD = (ZVM_boolTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_boolToSQWORD = (ZVM_boolTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_boolToUQWORD = (ZVM_boolTo | CchZVM_UQWORD_TYPE_TAG);

const TZVMICode ZVM_byteTo = 0x5F00;
const TZVMICode ZVM_byteToBool = (ZVM_byteTo | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteToSDWORD = (ZVM_byteTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_byteToUDWORD = (ZVM_byteTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_byteToSQWORD = (ZVM_byteTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_byteToUQWORD = (ZVM_byteTo | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_byteToDouble = (ZVM_byteTo | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_sdwordTo = 0x6000;
const TZVMICode ZVM_sdwordToBool = (ZVM_sdwordTo | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_sdwordToByte = (ZVM_sdwordTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordToUDWORD = (ZVM_sdwordTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sdwordToSQWORD = (ZVM_sdwordTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_sdwordToUQWORD = (ZVM_sdwordTo | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_sdwordToDouble = (ZVM_sdwordTo | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_udwordTo = 0x6100;
const TZVMICode ZVM_udwordToBool = (ZVM_udwordTo | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_udwordToByte = (ZVM_udwordTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_udwordToSDWORD = (ZVM_udwordTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordToSQWORD = (ZVM_udwordTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_udwordToUQWORD = (ZVM_udwordTo | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_udwordToDouble = (ZVM_udwordTo | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_sqwordTo = 0x6200;
const TZVMICode ZVM_sqwordToBool = (ZVM_sqwordTo | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_sqwordToByte = (ZVM_sqwordTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sqwordToSDWORD = (ZVM_sqwordTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordToUDWORD = (ZVM_sqwordTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordToUQWORD = (ZVM_sqwordTo | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordToDouble = (ZVM_sqwordTo | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_uqwordTo = 0x6300;
const TZVMICode ZVM_uqwordToBool = (ZVM_uqwordTo | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_uqwordToByte = (ZVM_uqwordTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_uqwordToSDWORD = (ZVM_uqwordTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordToUDWORD = (ZVM_uqwordTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordToSQWORD = (ZVM_uqwordTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordToDouble = (ZVM_uqwordTo | CchZVM_DOUBLE_TYPE_TAG);

const TZVMICode ZVM_doubleTo = 0x6400;
const TZVMICode ZVM_doubleToByte = (ZVM_doubleTo | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_doubleToSDWORD = (ZVM_doubleTo | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_doubleToUDWORD = (ZVM_doubleTo | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_doubleToSQWORD = (ZVM_doubleTo | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleToUQWORD = (ZVM_doubleTo | CchZVM_UQWORD_TYPE_TAG);
//@}

/**
 * @name Stack指令
 */
const TZVMICode ZVM_pop = 0x6500;
const TZVMICode ZVM_popAny = (ZVM_pop | CchZVM_VOID_TYPE_TAG);
const TZVMICode ZVM_popBool = (ZVM_pop | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_popByte = (ZVM_pop | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_popSDWORD = (ZVM_pop | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_popUDWORD = (ZVM_pop | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_popSQWORD = (ZVM_pop | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_popUQWORD = (ZVM_pop | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_popDouble = (ZVM_pop | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_popString = (ZVM_pop | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_popRope = (ZVM_pop | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_popIPv4Address = (ZVM_pop | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_popPPort = (ZVM_pop | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_popTable = (ZVM_pop | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_ret = 0x6600 | CchZVM_VOID_TYPE_TAG;
const TZVMICode ZVM_pushBP = 0x6700 | CchZVM_VOID_TYPE_TAG;

const TZVMICode ZVM_construct = 0x6800;
const TZVMICode ZVM_constructBool = (ZVM_construct | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_constructByte = (ZVM_construct | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_constructSDWORD = (ZVM_construct | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_constructUDWORD = (ZVM_construct | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_constructSQWORD = (ZVM_construct | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_constructUQWORD = (ZVM_construct | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_constructDouble = (ZVM_construct | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_constructString = (ZVM_construct | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_constructRope = (ZVM_construct | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_constructIPv4Address = (ZVM_construct | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_constructPPort = (ZVM_construct | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_constructTable = 0x6900;
const TZVMICode ZVM_constructBoolTable = (ZVM_constructTable | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_constructByteTable = (ZVM_constructTable | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_constructSDWORDTable = (ZVM_constructTable | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_constructUDWORDTable = (ZVM_constructTable | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_constructSQWORDTable = (ZVM_constructTable | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_constructUQWORDTable = (ZVM_constructTable | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_constructDoubleTable = (ZVM_constructTable | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_constructStringTable = (ZVM_constructTable | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_constructRopeTable = (ZVM_constructTable | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_constructIPv4AddressTable = (ZVM_constructTable | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_constructPPortTable = (ZVM_constructTable | CchZVM_PPORT_TYPE_TAG);

const TZVMICode ZVM_constructReference = 0x6A00;
const TZVMICode ZVM_constructBoolReference = (ZVM_constructReference | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_constructByteReference = (ZVM_constructReference | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_constructSDWORDReference = (ZVM_constructReference | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_constructUDWORDReference = (ZVM_constructReference | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_constructSQWORDReference = (ZVM_constructReference | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_constructUQWORDReference = (ZVM_constructReference | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_constructDoubleReference = (ZVM_constructReference | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_constructStringReference = (ZVM_constructReference | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_constructRopeReference = (ZVM_constructReference | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_constructIPv4AddressReference = (ZVM_constructReference | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_constructPPortReference = (ZVM_constructReference | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_constructTableReference = (ZVM_constructReference | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_quickConstructObject = 0x6B00;
const TZVMICode ZVM_quickConstructStringObject = (ZVM_quickConstructObject | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_quickConstructRopeObject = (ZVM_quickConstructObject | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_quickConstructIPv4AddressObject = (ZVM_quickConstructObject | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_quickConstructPPortObject = (ZVM_quickConstructObject | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_quickConstructTableObject = (ZVM_quickConstructObject | CchZVM_TABLE_TYPE_TAG);
//@}

/**
 * @name PC转移指令
 */
//@{
const TZVMICode ZVM_falseJump = 0x8000;
const TZVMICode ZVM_boolFalseJump = (ZVM_falseJump | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteFalseJump = (ZVM_falseJump | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordFalseJump = (ZVM_falseJump | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordFalseJump = (ZVM_falseJump | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordFalseJump = (ZVM_falseJump | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordFalseJump = (ZVM_falseJump | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleFalseJump = (ZVM_falseJump | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringFalseJump = (ZVM_falseJump | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeFalseJump = (ZVM_falseJump | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_ipv4addressFalseJump = (ZVM_falseJump | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_pportFalseJump = (ZVM_falseJump | CchZVM_PPORT_TYPE_TAG);
const TZVMICode ZVM_tableFalseJump = (ZVM_falseJump | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_falseCircuitJump = 0x8100;
const TZVMICode ZVM_boolFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_ipv4addressFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_pportFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_PPORT_TYPE_TAG);
//const TZVMICode ZVM_tableFalseCircuitJump = (ZVM_falseCircuitJump | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_trueCircuitJump = 0x8200;
const TZVMICode ZVM_boolTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_BOOL_TYPE_TAG);
const TZVMICode ZVM_byteTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_BYTE_TYPE_TAG);
const TZVMICode ZVM_sdwordTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_SDWORD_TYPE_TAG);
const TZVMICode ZVM_udwordTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_UDWORD_TYPE_TAG);
const TZVMICode ZVM_sqwordTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_SQWORD_TYPE_TAG);
const TZVMICode ZVM_uqwordTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_UQWORD_TYPE_TAG);
const TZVMICode ZVM_doubleTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_DOUBLE_TYPE_TAG);
const TZVMICode ZVM_stringTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_STRING_TYPE_TAG);
const TZVMICode ZVM_ropeTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_ROPE_TYPE_TAG);
const TZVMICode ZVM_ipv4addressTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_IPv4ADDR_TYPE_TAG);
const TZVMICode ZVM_pportTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_PPORT_TYPE_TAG);
//const TZVMICode ZVM_tableTrueCircuitJump = (ZVM_trueCircuitJump | CchZVM_TABLE_TYPE_TAG);

const TZVMICode ZVM_unlimitJump = 0x8300 | CchZVM_VOID_TYPE_TAG;
const TZVMICode ZVM_call = 0x8400 | CchZVM_VOID_TYPE_TAG;
//@}


ZLS_END_NAMESPACE


#endif

