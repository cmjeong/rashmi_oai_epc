<?xml version="1.0" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:mib="http://www.Radisys.com/umts-fap/mib">
  <xsl:template match="childObject">
    <edge isdirected="true">
      <xsl:attribute name="id"><xsl:value-of select="../../@name"/>--<xsl:value-of select="@name"/></xsl:attribute> 
      <xsl:attribute name="from"><xsl:value-of select="../../@name"/></xsl:attribute> 
      <xsl:attribute name="to"><xsl:value-of select="@name"/></xsl:attribute> 
    </edge>
  </xsl:template>

  <xsl:template match="managedObject">
    <node>
      <xsl:attribute name="id"><xsl:value-of select="@name"/></xsl:attribute>
      <xsl:attribute name="name"><xsl:value-of select="@name"/></xsl:attribute>
    </node>
    <xsl:apply-templates select="childObjects/childObject"/>
 </xsl:template>

 <xsl:template match="/">
   <gxl>
 	 <graph id="moTree" edgeids="true" edgemode="directed">
       <attr name="node:shape" kind="node">
         <string>record</string>
       </attr>

       <xsl:apply-templates select="mib:mib/managedObjects/managedObject"/>
     </graph>
   </gxl>
   
 </xsl:template>

</xsl:stylesheet>
