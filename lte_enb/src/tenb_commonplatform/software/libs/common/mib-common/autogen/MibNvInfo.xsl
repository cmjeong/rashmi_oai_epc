<?xml version="1.0" ?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" xmlns:mib="http://www.Radisys.com/umts-fap/mib"> 

  <xsl:variable name="newline"><xsl:text disable-output-escaping = "yes">
  </xsl:text></xsl:variable>

  <!-- handle attribute on mo where attribute's base is non-volatile -->
  <xsl:template match="attribute" mode="defIsNV">
    <xsl:choose>
      <xsl:when test="not(@storageClass='VOLATILE')">
        <referencedBy><xsl:value-of select="../../@name"/></referencedBy>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <!-- handle attribute on mo where attribute's base is volatile -->
  <xsl:template match="attribute" mode="defIsNotNV">
    <xsl:choose>
      <xsl:when test="@storageClass='NON_VOLATILE'">
        <referencedBy><xsl:value-of select="../../@name"/></referencedBy>
      </xsl:when>
    </xsl:choose>
  </xsl:template>


  <!-- the attributeDef path -->
  <xsl:template match="attributeDef|attributeEnumDef">
    <!-- collate the nv attribute definitions -->
    <xsl:variable name="attributeName"><xsl:value-of select="@name"/></xsl:variable>
    <xsl:choose>
      <!-- print out all references to this attribute where storageClass is not changed to 'VOLATILE' -->
      <xsl:when test="@storageClass='NON_VOLATILE'">
        <xsl:value-of select="$newline"/>
        <parsedAttributeDef>
          <xsl:value-of select="@name"/><xsl:text disable-output-escaping = "yes"> type="</xsl:text><xsl:value-of select="@type"/><xsl:text disable-output-escaping = "yes">" min="</xsl:text><xsl:value-of select="@min"/><xsl:text disable-output-escaping = "yes">"  max="</xsl:text>  <xsl:value-of select="@max"/>  <xsl:text disable-output-escaping = "yes">" default="</xsl:text><xsl:value-of select="@default"/><xsl:text disable-output-escaping = "yes">" schema="</xsl:text><xsl:value-of select="@schema"/><xsl:text disable-output-escaping = "yes">"</xsl:text> 


          <!-- list managedObjects that use NV attributes -->
          <xsl:apply-templates select="../../managedObjects/managedObject/attributes/attribute[@name=$attributeName]" mode="defIsNV"/>
        </parsedAttributeDef>
      </xsl:when>
      <xsl:when test="../../managedObjects/managedObject/attributes/attribute[@name=$attributeName and @storageClass='NON_VOLATILE']">
        <xsl:value-of select="$newline"/>
        <parsedAttributeDef>
          <xsl:value-of select="@name"/><xsl:text disable-output-escaping = "yes"> type="</xsl:text><xsl:value-of select="@type"/><xsl:text disable-output-escaping = "yes">" min="</xsl:text><xsl:value-of select="@min"/><xsl:text disable-output-escaping = "yes">"  max="</xsl:text>  <xsl:value-of select="@max"/>  <xsl:text disable-output-escaping = "yes">" default="</xsl:text><xsl:value-of select="@default"/><xsl:text disable-output-escaping = "yes">" schema="</xsl:text><xsl:value-of select="@schema"/><xsl:text disable-output-escaping = "yes">"</xsl:text> 


          <!-- list managedObjects that use NV attributes -->
          <xsl:apply-templates select="../../managedObjects/managedObject/attributes/attribute[@name=$attributeName]" mode="defIsNotNV"/>
        </parsedAttributeDef>
      </xsl:when>
    </xsl:choose>
  </xsl:template>

  <!-- top matching template to pass the call down to the bottom template -->
  <xsl:template match="/">
    <nvInfo>
      <xsl:apply-templates select="mib:mib/attributeDefs/*"/><xsl:text>
</xsl:text></nvInfo>
  </xsl:template>


</xsl:stylesheet>
