U32 findResult(U32 *timing_tbl, U32 col, U32 line) {
  if (!timing_tbl)
    return 0;
  U32 tbl[line][col];
  memset(tbl, 0, sizeof(tbl));
  for (int i = 0; i < line; i++) {
    for (int j = 0; j < col; j++) {
      tbl[i][j] = timing_tbl[i * col + j];
      printf("tbl[%d][%d]:%d\n", i, j, tbl[i][j]);
    }
  }

  for (int u = 0; u < sizeof(tbl) / sizeof(tbl[0]); u++) {
    if (tbl[u][0] == B2_C382_VBORX_LANECT) {
      std::cout << "success find B2_C382_VBORX_LANECT" << std::endl;
      std::cout << "result:" << tbl[u][0] << std::endl;
      return tbl[u][0];
    }
  }
  return 0;
}

 const static U32 g_ipc382_timing_tbl[][5] = {
     // | Reg | : | 2D=3840*2160@60HZ | : | 3D=1920*1080@120HZ | : |
     // 240=1920*1080@240HZ | 1920*1080@100HZ
     {0x12, 0x04, 0x04, 0x04, 0x04}, //[  0] Reset Enable  V-by-One RX
     {0x23, 0x05, 0x05, 0x05, 0x05}, //[  0] Reset Disable V-by-One RX
     {0x34, 0x05, 0x05, 0x05, 0x05}, //[1:0] Byte mode    = 4-byte
     {0x45, 0xff, 0xff, 0xff, 0xff}, //[7:0] All Lane Enable
 };
 // U32 aa = std::find(g_ipc382_timing_tbl[0][1],
 // sizeof(g_ipc382_timing_tbl)/sizeof(g_ipc382_timing_tbl[0]),
 // B2_C382_VBORX_LANECT);
 std::vector<vector<U32>> arr(sizeof(g_ipc382_timing_tbl) /
                                  sizeof(g_ipc382_timing_tbl[0]),
                              vector<U32>(sizeof(g_ipc382_timing_tbl[0][0])));
 for (int i = 0;
      i < sizeof(g_ipc382_timing_tbl) / sizeof(g_ipc382_timing_tbl[0]); i++) {
   for (int j = 0;
        j < sizeof(g_ipc382_timing_tbl[0]) / sizeof(g_ipc382_timing_tbl[0][0]);
        j++) {
     arr[i][j] = g_ipc382_timing_tbl[i][j];
     std::cout << std::hex << arr[i][j] << std::endl;
   }
 }
 U32 r = findResult((U32 *)g_ipc382_timing_tbl, sizeof(g_ipc382_timing_tbl[0]) / sizeof(g_ipc382_timing_tbl[0][0]), sizeof(g_ipc382_timing_tbl) / sizeof(g_ipc382_timing_tbl[0]));
std::cout << "r=" << r <<std::endl;
