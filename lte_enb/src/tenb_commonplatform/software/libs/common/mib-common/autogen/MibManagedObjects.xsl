<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet xmlns:mib="http://www.Radisys.com/umts-fap/mib" xsl:version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">

<xsl:template match="/">
<mib>
 <noprocess><![CDATA[///////////////////////////////////////////////////////////////////////////////
//
// MibManagedObjects.h
//
// Descriptors of all available MIB objects.
// THIS FILE IS AUTOGENERATED
//
// Copyright Radisys Limited
//
///////////////////////////////////////////////////////////////////////////////

#ifndef __MibManagedObjects_h_
#define __MibManagedObjects_h_

///////////////////////////////////////////////////////////////////////////////
// System Includes
///////////////////////////////////////////////////////////////////////////////

#include <Radisys.h>

///////////////////////////////////////////////////////////////////////////////
// Local Includes
///////////////////////////////////////////////////////////////////////////////

#include <mib-common/MibObjectDescriptors.h>
#include <mib-common/MibAttributeDescriptors.h>

///////////////////////////////////////////////////////////////////////////////
// Constants
///////////////////////////////////////////////////////////////////////////////
]]></noprocess>
  <!-- Create the <MO>ValidChildObject arrays --> 
  <xsl:for-each select="mib:mib/managedObjects/managedObject">
    <twoDimensionArray type="MibChildObjectDescriptor">
      <xsl:attribute name="name"><xsl:value-of select="@name"/>ValidChildClasses</xsl:attribute>
      <xsl:for-each select="childObjects/childObject">
        <xsl:sort select="@name"/>
        <array>
          <entity>MIB_OBJECT_CLASS_<xsl:value-of select="translate(@name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/></entity>
          <!-- @minInstances -->
          <xsl:choose>
            <xsl:when test="@minInstances"><entity><xsl:value-of select="@minInstances"/>U</entity></xsl:when>
            <xsl:otherwise><entity>0U</entity></xsl:otherwise>
          </xsl:choose>
          <!-- max -->
          <xsl:choose>
            <xsl:when test="@maxInstances"><entity><xsl:value-of select="@maxInstances"/>U</entity></xsl:when>
            <xsl:otherwise><entity><![CDATA[std::numeric_limits<u32>::max()]]></entity></xsl:otherwise>
          </xsl:choose>
        </array>
      </xsl:for-each>
    </twoDimensionArray>
  </xsl:for-each>

  <!-- Create the <MO>ValidAttribute array -->
  <xsl:for-each select="mib:mib/managedObjects/managedObject">
    <twoDimensionArray type="MibObjectAttributeDescriptor">
      <xsl:attribute name="name"><xsl:value-of select="@name"/>ValidAttributeIds</xsl:attribute>
      <xsl:apply-templates select="attributes/attribute"/>
    </twoDimensionArray>
  </xsl:for-each>

  <noprocess><![CDATA[/**
 * MO meta-data is constant information so we define it in a constant
 * table here.  We can then still dynamically create/delete MOs but
 * their properties (valid attributes, valid parent, valid children...) are
 * fixed for a particular build.
 */
]]></noprocess>

  <!-- This creates the data structure for the mibManagedObjectDescriptors array -->
  <twoDimensionArray name="mibManagedObjectDescriptors" type="MibManagedObjectDescriptor">
    <xsl:for-each select="mib:mib/managedObjects/managedObject">
      <xsl:sort select="@name"/>
      <array>
        <entity>"<xsl:value-of select="@name"/>"</entity>
        <entity>MIB_OBJECT_CLASS_<xsl:value-of select="translate(@name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/></entity>
        <entity>
          <xsl:choose>
            <xsl:when test="@parent">MIB_OBJECT_CLASS_<xsl:value-of select="translate(@parent,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')"/></xsl:when>
            <xsl:otherwise>MIB_OBJECT_CLASS_ROOT</xsl:otherwise>
          </xsl:choose>
        </entity>
  
        <entity><xsl:value-of select="@name"/>ValidChildClasses</entity>
        <entity><xsl:value-of select="count(childObjects/childObject)"/></entity>
  
        <entity><xsl:value-of select="@name"/>ValidAttributeIds</entity>
        <entity>sizeof(<xsl:value-of select="@name"/>ValidAttributeIds)/sizeof(MibObjectAttributeDescriptor)</entity>
      </array>
    </xsl:for-each>
  </twoDimensionArray>

  <scalar name="mibManagedObjectDescriptorsNum" type="int">
    <xsl:value-of select="count(/mib:mib/managedObjects/managedObject)"/>
  </scalar>

  <noprocess><![CDATA[#endif]]></noprocess>

</mib>
</xsl:template>

<!-- match attribute and handle object attribute inheritance -->
<xsl:template match="attributeDef|attributeEnumDef">
  <xsl:param name = "moAccessClass"/>  
  <xsl:param name = "moStorageClass"/>

  <array>
    <entity>PARAM_ID_<xsl:value-of select="translate(@name,'abcdefghijklmnopqrstuvwxyz','ABCDEFGHIJKLMNOPQRSTUVWXYZ')" /></entity>
    <!-- access class -->
    <xsl:choose>
      <!-- check object first -->
      <xsl:when test="string($moAccessClass)">
        <entity>MIB_ACCESS_<xsl:value-of select="$moAccessClass"/></entity>
      </xsl:when>
      <!-- then check attribute -->
      <xsl:when test="string(@accessClass)">
        <entity>MIB_ACCESS_<xsl:value-of select="@accessClass"/></entity>
      </xsl:when>
      <xsl:otherwise>
        <!-- this attribute must be spec'd somewhere, there is no default -->
        <entity>"XML error: please provide an accessClass attribute for <xsl:value-of select="@name"/>"</entity>
      </xsl:otherwise>
    </xsl:choose>
    <!-- storage class -->
    <xsl:choose>
      <!-- check object first -->
      <xsl:when test="string($moStorageClass)">
        <entity>MIB_STORAGE_<xsl:value-of select="$moStorageClass"/></entity>
      </xsl:when>
      <!-- then check attribute -->
      <xsl:when test="string(@storageClass)">
        <entity>MIB_STORAGE_<xsl:value-of select="@storageClass"/></entity>
      </xsl:when>
      <xsl:otherwise>
        <!-- this attribute must be spec'd somewhere, there is no default -->
        <entity>"XML error: please provide a storageClass attribute for <xsl:value-of select="@name"/>"</entity>
      </xsl:otherwise>
    </xsl:choose>
  </array>

</xsl:template>

<xsl:template match="attribute">
  <xsl:variable name="attribute"><xsl:value-of select="@name" /></xsl:variable>
  <xsl:apply-templates select="../../../../attributeDefs/attributeEnumDef[@name=$attribute]|../../../../attributeDefs/attributeDef[@name=$attribute]">
    <xsl:with-param name="moAccessClass"><xsl:value-of select="@accessClass"/></xsl:with-param>
    <xsl:with-param name="moStorageClass"><xsl:value-of select="@storageClass"/></xsl:with-param>
  </xsl:apply-templates>

</xsl:template>

</xsl:stylesheet>
