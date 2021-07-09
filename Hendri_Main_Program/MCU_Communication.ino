void sendDataMCU(String ec, String ph, String suhu, String kel, String uv)
{
  // sendDatatoMCU(nilai_EC, nilai_pH, nilai_suhu, nilai_kel, nilai_uv);
  //sendDatatoMCU(String(ecValue, 1), String(pHValue), String(temp), String(hum), String(indexUV));
  //|ec|ph|suhu|klel|uv|
  String dataSend = "|";
  dataSend += ec;
  dataSend += "|";
  dataSend += ph;
  dataSend += "|";
  dataSend += suhu;
  dataSend += "|";
  dataSend += kel;
  dataSend += "|";
  dataSend += uv;
  dataSend += "|\r";
  Serial.println(dataSend);
  MCU.print(dataSend);
}

void reciveDataMCU()
{
  if (MCU.available() > 0)
  {
    int ind1, ind2, ind3, ind4, ind5, ind6, ind7, ind8, ind9, ind10;
    String data1, data2, data3, data4, data5, data6, data7, data8, data9;
    //    sendDataArd(ph_a, ph_b, ppm_a, ppm_b, suhu_a, suhu_b, kel_a, kel_b, cahaya);
    String req = MCU.readStringUntil('\r');
    Serial.println(req);
    req.toLowerCase();
    //sendDatatoMCU(String(ecValue, 1), String(pHValue), String(temp), String(hum), String(indexUV));
    if (req.length() > 0)
    {
      ind1 = req.indexOf('|');
      ind2 = req.indexOf('|', ind1 + 1);
      ind3 = req.indexOf('|', ind2 + 1);
      ind4 = req.indexOf('|', ind3 + 1);
      ind5 = req.indexOf('|', ind4 + 1);
      ind6 = req.indexOf('|', ind5 + 1);
      ind7 = req.indexOf('|', ind6 + 1);
      ind8 = req.indexOf('|', ind7 + 1);
      ind9 = req.indexOf('|', ind8 + 1);
      ind10 = req.indexOf('|', ind9 + 1);
      data1 = req.substring(ind1 + 1, ind2); // ec batas bawah
      data2 = req.substring(ind2 + 1, ind3); // ec batas atas
      data3 = req.substring(ind3 + 1, ind4); // ph batas bawah
      data4 = req.substring(ind4 + 1, ind5);// ph batas atas
      data5 = req.substring(ind5 + 1, ind6);// suhu batas bawah
      data6 = req.substring(ind6 + 1, ind7);// suhu batas atas
      data7 = req.substring(ind7 + 1, ind8);// kel batas bawah
      data8 = req.substring(ind8 + 1, ind9); // kel batas atas
      data9 = req.substring(ind8 + 1, ind9); // Cahaya
      ph_a = toF(data1);
      ph_b = toF(data2);
      ec_a = toF(data3);
      ec_b = toF(data4);
      temp_a = toF(data5);
      temp_b = toF(data6);
      hum_a = toF(data7);
      hum_b = toF(data8);
      lux_a = toF(data9);
    }
  }
}

float toF(String in )
{
  float F = in.toFloat();
  return F;
}
