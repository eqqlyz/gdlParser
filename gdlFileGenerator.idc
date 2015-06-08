//用于从IDA上批量输出GDL文件
#include <idc.idc>
static main() {
   auto addr, name, end, funcFlags, seg;
   addr = 0;
   for (addr = NextFunction(addr); addr != BADADDR; addr = NextFunction(addr)) {
	  // Get the function name at address addr
      name = Name(addr);
	  // Get the segment of the function func
	  seg = SegName(addr);
	  // Get the end address of the current function
	  end = GetFunctionAttr(addr, FUNCATTR_END);
	  // Get the attribute of the current function
	  funcFlags = GetFunctionFlags(addr);
	  // Only output the function in text area
	  if((funcFlags == FUNC_STATIC) && (seg == ".extern")){
		GenFuncGdl(name,name,addr,end,CHART_GEN_GDL);
	  }
   }
}