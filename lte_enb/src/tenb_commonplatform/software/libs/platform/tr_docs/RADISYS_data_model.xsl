<?xml version="1.0" encoding="utf-8"?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform" version="1.0">
  <xsl:output method="html"/>

  <xsl:variable name="Integrator" select="integrator"></xsl:variable>

  <xsl:variable name="filename_tr196" select="'./tr-196-2-0-1.xml'"></xsl:variable>
  <xsl:variable name="filename_tr098" select="'./tr-098_RADISYS.xml'"></xsl:variable>
  <xsl:variable name="filename_extension" select="'./RADISYS_data_model_extension.xml'"></xsl:variable>
  <xsl:variable name="filename_review" select="'Reviews.xml'"></xsl:variable>

  <xsl:variable name="tr196" select="document($filename_tr196)"></xsl:variable>
  <xsl:variable name="tr098" select="document($filename_tr098)"></xsl:variable>
  <xsl:variable name="extension" select="document($filename_extension)"></xsl:variable>
  <xsl:variable name="review" select="document($filename_review)"></xsl:variable>

  <xsl:variable name="tr196_name" select="'TR-196'"></xsl:variable>
  <xsl:variable name="tr098_name" select="'TR-098'"></xsl:variable>
  <xsl:variable name="extension_name" select="'RADISYS'"></xsl:variable>

  <xsl:template match="/">
    <html>
      <body>
        <!--
             <xsl:choose>
               <xsl:when test="function-available('replace')">
                 <p>replace() is supported.</p>
               </xsl:when>
               <xsl:otherwise>
                 <p>replace() is not supported.</p>
               </xsl:otherwise>
             </xsl:choose>
         -->
             <xsl:choose>
               <xsl:when test="$Integrator='RADISYS'">
                 <h1>RADISYS HNB - Standard Data Model </h1>
               </xsl:when>
               <xsl:otherwise>
                 <h1>RADISYS HNB - Data Model - Integrator: "<xsl:value-of select="$Integrator"/>"</h1>
               </xsl:otherwise>
             </xsl:choose>
        <h2>Content:</h2>
        <dl>
          <dt style="font-weight: bold"><xsl:value-of select="$tr196_name"/></dt>
          <dd>file name: "<xsl:value-of select="$filename_tr196"/>"</dd>
          <dd>Supported: <a href="#tr196_o">object list</a> and <a href="#tr196_p">parameter list</a></dd>
          <dd>Reference: [TR196] Broadband Forum, "Femto Access Point Service Data Model", Technical Report, Issue 1, April, 2009</dd>
          <dt style="font-weight: bold"> <xsl:value-of select="$tr098_name"/> : </dt>
          <dd>file name: "<xsl:value-of select="$filename_tr098"/>"</dd>
          <dd>Supported: <a href="#tr098_o">object list</a> and <a href="#tr098_p">parameter list</a></dd>
          <dd>Reference: [TR098] Broadband Forum, "Internet Gateway Device Data Model for TR-069", Technical Report, Issue: 1 Amendment 2, Issue Date: September 2008 </dd>
          <dt style="font-weight: bold">Supported vendors extensions</dt>
          <dd>file name: "<xsl:value-of select="$filename_extension"/>"</dd>
          <dd>Supported: <a href="#extension_o">object list</a>, <a href="#extension_p">parameter list</a></dd>
          <dd>Description: RADISYS's HNB supported extension to Internet Gateway Device Data Model for TR-069</dd>
        </dl>
        
	<h2>Notes</h2>
	<dl>
		<dt>Only those parameters marked in GREEN (Release='2.1')
			shall be implemented</dt>
		<dt> Those parameters marked in RED (Release='-') shall
			not be supported in this release of the
			HNB</dt>
	</dl>

        <h1><xsl:value-of select="$tr196_name" /></h1>
        <!--
        <h2>Reviews summary</h2>
        <xsl:call-template name="Reviews">
          <xsl:with-param name="file" select="$review"/>
        </xsl:call-template>
        -->
        <h2>TR-196 Summary</h2>
        <xsl:call-template name="Summary">
          <xsl:with-param name="file" select="$tr196"/>
          <xsl:with-param name="fname" select="$tr196_name"/>
        </xsl:call-template>
        <h2><a name="tr196_o">TR-196 Object summary</a></h2>
        <xsl:call-template name="objSummary">
          <xsl:with-param name="file" select="$tr196"/>
          <xsl:with-param name="fname" select="$tr196_name"/>
        </xsl:call-template>
        <h2><a name="tr196_p">TR-196 Parameters</a></h2>
        <xsl:call-template name="model">
          <xsl:with-param name="file" select="$tr196"/>
          <xsl:with-param name="fname" select="$tr196_name"/>
        </xsl:call-template>

        <h1><xsl:value-of select="$tr098_name" /></h1>
        <!--
        <h2>TR-098 Summary</h2>
        <xsl:call-template name="Summary">
          <xsl:with-param name="file" select="$tr098"/>
          <xsl:with-param name="fname" select="$tr098_name"/>
        </xsl:call-template>
        -->
        <h2><a name="tr098_o">TR-098 Object summary</a></h2>
        <xsl:call-template name="objSummary">
          <xsl:with-param name="file" select="$tr098"/>
          <xsl:with-param name="fname" select="$tr098_name"/>
        </xsl:call-template>
        <h2><a name="tr098_p">TR-098 Parameters</a></h2>
        <xsl:call-template name="model">
          <xsl:with-param name="file" select="$tr098"/>
          <xsl:with-param name="fname" select="$tr098_name"/>
        </xsl:call-template>

        <h1>Supported Vendor's extensions</h1>
        <!--
        <h2>Extension Summary</h2>
        <xsl:call-template name="Summary">
          <xsl:with-param name="file" select="$extension"/>
          <xsl:with-param name="fname" select="$extension_name"/>
        </xsl:call-template>
        -->
        <h2><a name="extension_o">Extension Object summary</a></h2>
        <xsl:call-template name="objSummary">
          <xsl:with-param name="file" select="$extension"/>
          <xsl:with-param name="fname" select="$extension_name"/>
        </xsl:call-template>
        <h2><a name="extension_p">Extension Parameters</a></h2>
        <xsl:call-template name="model">
          <xsl:with-param name="file" select="$extension"/>
          <xsl:with-param name="fname" select="$extension_name"/>
        </xsl:call-template>

      </body>
    </html>
  </xsl:template>

  <xsl:template match="syntax">
    <!--<xsl:value-of select="local-name(*)"/>:<xsl:apply-templates select="current()/text()"/>-->
    <!-- <xsl:value-of select="local-name(*)"/>-->
    <xsl:choose>
      <xsl:when test = "string">string 
        <xsl:choose>
          <xsl:when test = "list"><xsl:apply-templates select="list/size" /></xsl:when>
          <xsl:when test = "string"><xsl:apply-templates select="string/size" /></xsl:when>
        </xsl:choose>
      </xsl:when>
      <xsl:when test = "unsignedInt">unsignedInt
        <xsl:choose>
          <xsl:when test = "list"><xsl:apply-templates select="list/size" /></xsl:when>
          <xsl:when test = "unsignedInt/range">
            <xsl:apply-templates select="unsignedInt" />
          <!--[<xsl:apply-templates select="unsignedInt/range" />]-->
        </xsl:when>
        </xsl:choose>
      </xsl:when>
      <xsl:when test = "int">int
        <xsl:choose>
          <xsl:when test = "list"><xsl:apply-templates select="list/size" /></xsl:when>
          <xsl:when test = "int/range">
            <xsl:apply-templates select="int" />
            <!--[<xsl:apply-templates select="int/range" />]-->
        </xsl:when>
      </xsl:choose>
      </xsl:when>
      <xsl:when test = "boolean">boolean</xsl:when>
      <xsl:when test = "dateTime">dateTime</xsl:when>
      <xsl:when test = "dataType">        
        <xsl:apply-templates select="dataType" />
      </xsl:when>
      <xsl:otherwise>
        ERROR: UNKWNOWN SYNTAX
      </xsl:otherwise>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="unsignedInt">
    <xsl:variable name="the_min">
      <xsl:for-each select="range/@minInclusive">
        <xsl:sort data-type="number" order="ascending"/>
        <xsl:if test="position()=1"><xsl:value-of select="."/></xsl:if>
      </xsl:for-each>
    </xsl:variable>
   <xsl:variable name="the_max">
     <xsl:for-each select="range/@maxInclusive">
       <xsl:sort data-type="number" order="descending"/>
       <xsl:if test="position()=1"><xsl:value-of select="."/></xsl:if>
     </xsl:for-each>
   </xsl:variable>
   [<xsl:value-of select="$the_min"/>:<xsl:value-of select="$the_max"/>]
  </xsl:template>

  <xsl:template match="int">
    <xsl:variable name="the_min">
      <xsl:for-each select="range/@minInclusive">
        <xsl:sort data-type="number" order="ascending"/>
        <xsl:if test="position()=1"><xsl:value-of select="."/></xsl:if>
      </xsl:for-each>
    </xsl:variable>
   <xsl:variable name="the_max">
     <xsl:for-each select="range/@maxInclusive">
       <xsl:sort data-type="number" order="descending"/>
       <xsl:if test="position()=1"><xsl:value-of select="."/></xsl:if>
     </xsl:for-each>
   </xsl:variable>
   [<xsl:value-of select="$the_min"/>:<xsl:value-of select="$the_max"/>]
  </xsl:template>
      
  <xsl:template match="range">
    <xsl:choose>
      <xsl:when test = "@minInclusive"><xsl:value-of select="@minInclusive"/>
    </xsl:when></xsl:choose>:<xsl:choose>
    <xsl:when test = "@maxInclusive"><xsl:value-of select="@maxInclusive"/>
  </xsl:when></xsl:choose>
  </xsl:template>

  <xsl:template match="size">
    <xsl:choose>
      <xsl:when test = "@maxLength">(<xsl:value-of select="@maxLength" />)</xsl:when>
    </xsl:choose>
  </xsl:template>

  <xsl:template match="dataType">
    <xsl:value-of select="@ref"/>    
  </xsl:template>

  <xsl:template match="param|@*">
    <a href="#{id(@ref)/title}" />
  </xsl:template>

  <xsl:template name="bibref">
    <a href="#{@refid}" />
  </xsl:template>

  <xsl:template name="Reviews">
    <xsl:param name="file"/>
    <table border="1" width="80%" cellpadding="2" cellspacing="0"
      style="vertical-align: top; font-family: helvetica,arial,sans-serif; font-size: 8pt;">
      <tr bgcolor="cyan">
        <th width="5%">Item #</th>
        <th width="5%">Status</th>
        <th width="10%">TR: (id #)</th>
        <th width="40%">Issues</th>
        <th width="40%">Proposed solution</th>	
      </tr>
      <xsl:for-each select="$file//Review/item">
        <tr>
          <td align="center"><xsl:number count="item"/>.</td>
          <xsl:choose>
            <xsl:when test = "openClose = 'Closed'">
              <td bgcolor="green"><xsl:value-of select="openClose"/></td>
            </xsl:when>
            <xsl:when test ="openClose = 'Open'">
              <td bgcolor="red"><xsl:value-of select="openClose"/></td>
            </xsl:when>
          </xsl:choose>
          <td><xsl:value-of select="reference"/></td>
          <td><xsl:value-of select="issue"/></td>
          <td><xsl:value-of select="solution"/></td>	
        </tr>
      </xsl:for-each>
    </table>
  </xsl:template>

  <xsl:template name="Summary">
    <xsl:param name="file"/>
    <xsl:param name="fname"/>
    <table border="1" width="50%" cellpadding="2" cellspacing="0"
      style="vertical-align: top; font-family: helvetica,arial,sans-serif; font-size: 8pt;">
      <tr bgcolor="cyan">
        <th width="80%">Measure</th>
        <th width="20%">#</th>
      </tr>
      <tr align="center" bgcolor="yellow" style="font-weight: bold;">
        <td><xsl:value-of select="$fname" /> model</td><td></td>
      </tr>
      <tr>
        <td style="font-weight: bold;">Total number of parameters in the object model: </td>
        <td align="center"><xsl:value-of select="count($file//model/object/parameter)+
        count($file//model/parameter)"/></td>
      </tr>
      <tr>
        <td style="font-weight: bold;">Number of parameters configured by the FAP ("readOnly" in the data model): </td>
        <td align="center"><xsl:value-of select="count($file//model/object/parameter[@access='readOnly'])+
        count($file//model/parameter[@access='readOnly'])"/></td>
      </tr>
      <tr>
        <td style="font-weight: bold;">Number of parameters configured by the FGW ("readWrite" in the data model): </td>
        <td align="center"><xsl:value-of select="count($file//model/object/parameter[@access='readWrite'])+
        count($file//model/parameter[@access='readWrite'])"/></td>
      </tr>
      <tr align="center" bgcolor="yellow" style="font-weight: bold;"><td>Release 2.1: proposal</td><td></td></tr>
      <tr>
        <td style="font-weight: bold;">Number of parameters to be implemented in release 2.1: </td>
        <td align="center"><xsl:value-of select="count($file//model/object/parameter/RADISYS/default[@supported='TRUE'])+
        count($file//model/parameter/RADISYS/default[@supported='TRUE'])"/></td>
      </tr>
      <tr>
        <td style="font-weight: bold;">Number of parameters requiring decision: </td>
        <td align="center"><xsl:value-of select="count($file//model/object/parameter[not(RADISYS)])+
        count($file//model/object/parameter/RADISYS/default[supported!=0.0 and supported!=2.1])"/></td>
      </tr>
    </table>
  </xsl:template>

  <xsl:template name="objSummary">
    <xsl:param name="file"/>
    <xsl:param name="fname"/>
    <table border="1" width="80%" cellpadding="2" cellspacing="0"
      style="vertical-align: top; font-family: helvetica,arial,sans-serif; font-size: 8pt;">
      <tr style="font-weight: bold;">
        <th bgcolor="blue" width="3%" align="centre">#</th>
        <th bgcolor="cyan" width="17%" align="left">Name</th>
        <th bgcolor="cyan" width="25%" align="left">Description (part of...)</th>
        <th bgcolor="blue" width="5%" align="centre">Release</th>
        <th bgcolor="blue" width="30%" align="centre">Notes</th>
      </tr>
      <xsl:for-each select="$file//model/object">
          <xsl:choose>
            <xsl:when test="$fname=$tr196_name">
              <xsl:call-template name="object_out" />
            </xsl:when>
            <xsl:otherwise>
              <xsl:choose>            
                <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE']">
                <xsl:call-template name="object_out" />
              </xsl:when>
              <xsl:when test="RADISYS/override[@integrator=$Integrator and @visible='FALSE']">
			<tr> <!-- DO NOTHING  --></tr>
              </xsl:when>
              <xsl:when test="RADISYS/default[@supported='TRUE']">
                <xsl:call-template name="object_out" />
              </xsl:when>
             <xsl:otherwise><tr> <!-- DO NOTHING  --></tr></xsl:otherwise>
            </xsl:choose>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
    </table>
  </xsl:template>

  <xsl:template name="object_out">
    <tr bgcolor="#e7d433">
      <td align="center"><xsl:number count="object"/>.</td>
      <!--      <td><xsl:value-of select="@name"/></td> -->
      <td width="5%"> 
		  <xsl:choose>
			<xsl:when test = "RADISYS/override[@integrator=$Integrator and @name]">
				<p>	<xsl:apply-templates select="RADISYS/override[@integrator=$Integrator and @supported='TRUE']" mode="name"/> </p>
				<p>	(mapped to: <xsl:value-of select="@name" />) </p>
			</xsl:when>
			<xsl:otherwise>
			      <xsl:value-of select="@name" />
	      		</xsl:otherwise>
		</xsl:choose>
	</td>
      <td><xsl:value-of select="description"/></td>
      <xsl:apply-templates select="RADISYS" mode="object" />
      <!--<xsl:call-template name="Notes_disp" />-->
    </tr>    
  </xsl:template>

  <xsl:template name="model">
    <xsl:param name="file"/>
    <xsl:param name="fname"/>
    <xsl:for-each select="$file//model">
      <h2 style="font-family: helvetica,arial,sans-serif; font-size: 12pt;" ><xsl:value-of select="@name"/></h2>
    </xsl:for-each>
    <table border="1" width="90%" cellpadding="2" cellspacing="0"
      style="vertical-align: top; font-family: helvetica,arial,sans-serif; font-size: 8pt;">
      <tr style="font-weight: bold;">
        <xsl:call-template name="table" />
      </tr>

        <xsl:choose>
          <xsl:when test="$fname=$tr196_name or $fname=$tr098_name">
            <xsl:for-each select="$file//model/parameter">
              <tr>
                <td align="center">0.<xsl:number count="parameter"/></td>
                <xsl:call-template name="parameter" />
              </tr>
            </xsl:for-each>
          </xsl:when>
          <xsl:otherwise>
            <xsl:for-each select="$file//model/parameter">
              <tr>
                <p align="center"> ERROR: PARAMETERS NEED TO BE NESTED WITHIN OBJECT IN EXTENSION FILE</p>
              </tr>
            </xsl:for-each>
          </xsl:otherwise>
        </xsl:choose>

      <xsl:for-each select="$file//model/object">
        <xsl:choose>
          <xsl:when test="$fname=$tr196_name">
            <xsl:call-template name="parameter_obj">
              <xsl:with-param name="file" select="$file"/>
              <xsl:with-param name="fname" select="$fname"/>
            </xsl:call-template>
          </xsl:when>
          <xsl:otherwise>
	    <xsl:choose>
	      <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE']">
                <xsl:call-template name="parameter_obj">
                  <xsl:with-param name="file" select="$file"/>
                  <xsl:with-param name="fname" select="$fname"/>
                </xsl:call-template>
              </xsl:when>
             <xsl:when test="RADISYS/override[@integrator=$Integrator and @visible='FALSE']">
              <tr>  <!-- DO NOTHING  --> </tr>
             </xsl:when>
              <xsl:when test="RADISYS/default[@supported='TRUE']">
                <xsl:call-template name="parameter_obj">
                  <xsl:with-param name="file" select="$file"/>
                  <xsl:with-param name="fname" select="$fname"/>
                </xsl:call-template>
              </xsl:when>
              <xsl:otherwise><tr>  <!-- DO NOTHING  --> </tr></xsl:otherwise>
            </xsl:choose>
          </xsl:otherwise>
        </xsl:choose>
      </xsl:for-each>
    </table>
  </xsl:template>

  <xsl:template name="parameter_obj">
    <xsl:param name="file"/>
    <xsl:param name="fname"/>
    <xsl:call-template name="object" />
    <xsl:for-each select="parameter">
        <xsl:choose>
          <xsl:when test="$fname=$tr196_name">
            <tr>
              <td align="center"><xsl:number count="object" />.<xsl:number count="parameter" /></td>            
              <xsl:call-template name="parameter" />
            </tr>
          </xsl:when>
          <xsl:otherwise>
	    <xsl:choose>
	      <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE']">
                <tr>
                  <td align="center"><xsl:number count="object" />.<xsl:number count="parameter" /></td>            
                  <xsl:call-template name="parameter" />
                </tr>
	    </xsl:when>
	    <xsl:when test="RADISYS/override[@integrator=$Integrator and @visible='FALSE']">
		    <tr>  <!-- DO NOTHING  --> </tr>
              </xsl:when>
              <xsl:when test="RADISYS/default[@supported='TRUE']">
                <tr>
                  <td align="center"><xsl:number count="object" />.<xsl:number count="parameter" /></td>            
                  <xsl:call-template name="parameter" />
                </tr>
              </xsl:when>
             <xsl:otherwise><tr>  <!-- DO NOTHING  --> </tr></xsl:otherwise>
            </xsl:choose>
          </xsl:otherwise>
        </xsl:choose>
    </xsl:for-each>
  </xsl:template>

  <xsl:template name="parameter"> 
	  <td width="5%"> 
		  <xsl:choose>
			<xsl:when test = "RADISYS/override[@integrator=$Integrator and @name]">
				<p>	<xsl:apply-templates select="RADISYS/override[@integrator=$Integrator]" mode="name"/> </p>
				<p>	(mapped to: <xsl:value-of select="@name" />) </p>
			</xsl:when>
			<xsl:otherwise>
			      <xsl:value-of select="@name" />
	      		</xsl:otherwise>
		</xsl:choose>
	</td>
    <xsl:call-template name="Description" />
    <td><xsl:apply-templates select="syntax" /></td>
    <xsl:call-template name="Write" />
    <xsl:apply-templates select="RADISYS" mode="parameter"/>
    <xsl:call-template name="Notification" />
  </xsl:template>


  <xsl:template name="table">
    <th bgcolor="blue" style="width:4%;" align="centre">#</th>
    <th bgcolor="cyan" style="width:16%" align="left">Name</th>
    <th bgcolor="cyan" style="width:25%" align="left">Description (part of...)</th>
    <th bgcolor="cyan" style="width:5%" align="left">Syntax</th>
    <th bgcolor="cyan" style="width:5%" align="left">Write</th>
    <th bgcolor="blue" style="width:5%" align="centre">Rel.</th>
    <th bgcolor="blue" style="width:15%" align="center">Notes</th>
    <th bgcolor="blue" style="width:5%" align="center">FAP Value</th>
    <th bgcolor="blue" style="width:5%" align="center">Suggested Value</th>
    <th bgcolor="blue" style="width:5%" align="center">Notification Type</th>
  </xsl:template>

  <xsl:template name="object">
    <tr bgcolor="#e7d433">
	<td align="center"><xsl:number count="object"/>.</td>
	<!--	<td><xsl:value-of select="@name"/></td> -->
	<td width="5%"> 
	  <xsl:choose>
		<xsl:when test = "RADISYS/override[@integrator=$Integrator and @name]">
		<p>	<xsl:apply-templates select="RADISYS/override[@integrator=$Integrator and @supported='TRUE']" mode="name"/> </p>
		<p>	(mapped to: <xsl:value-of select="@name" />) </p>
		</xsl:when>
		<xsl:otherwise>
		      <xsl:value-of select="@name" />
   		</xsl:otherwise>
	  </xsl:choose>
	</td>
      <td><xsl:value-of select="description"/></td>
      <td>object</td>
      <xsl:call-template name="Write" />
      <xsl:apply-templates select="RADISYS" mode="object" /> 
      <td></td><td></td><td></td>
    </tr>
  </xsl:template>

  <xsl:template match="RADISYS" mode="object">
    <xsl:choose>
      <xsl:when test = "override[@integrator=$Integrator and @supported='TRUE']">
        <td align="center" bgcolor="lightgreen">2.1</td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and @supported='FALSE']">
        <td align="center" bgcolor="lightred">-</td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and not(@supported)]">
        <td align="center" bgcolor="gray">...</td>
      </xsl:when>
      <xsl:when test = "default[@supported='TRUE']">
        <td align="center" bgcolor="green">2.1</td>
      </xsl:when>
      <xsl:when test = "default[@supported='FALSE']">
        <td align="center" bgcolor="red">-</td>
      </xsl:when>
      <xsl:otherwise>
        <td align="center" bgcolor="yellow">??</td>
      </xsl:otherwise>
    </xsl:choose> 
    <td><xsl:call-template name="Notes_disp" /></td>
  </xsl:template>
  
  <xsl:template name="Description"> 
    <td class="p">
      <xsl:apply-templates select="description" />
      <xsl:choose>
        <xsl:when test = "syntax/string/enumeration">
          <p>{{enum}}=</p>
          <ul><xsl:apply-templates select="syntax/string/enumeration" /></ul>
        </xsl:when>
        <xsl:when test = "syntax/int">
          <ul>
            <xsl:apply-templates select="syntax/int/units" />
          </ul>
        </xsl:when>
        <xsl:when test = "syntax/unsignedInt">
          <ul>
            <xsl:apply-templates select="syntax/unsignedInt/units" />
          </ul>
        </xsl:when>
      </xsl:choose>
    </td>
  </xsl:template>
  
  <xsl:template match="description">
    <xsl:value-of select="." /> 
    <!--<xsl:value-of select="replace(.,'{{units}}','[SEE UNITS ON TR]')" /> -->
  </xsl:template>

  <xsl:template match="units">
    {{units}}=<xsl:value-of select="@value" /> 
    <!--<xsl:value-of select="replace(.,'{{units}}','[SEE UNITS ON TR]')" /> -->
  </xsl:template>
  
  <xsl:template match="enumeration">
    <li><i><xsl:value-of select="@value"/></i>
    <xsl:choose>
      <xsl:when test="description">
         (<xsl:value-of select="description"/>)
      </xsl:when>
    </xsl:choose>
  </li>
  </xsl:template>

  <xsl:template match="RADISYS" mode="parameter">
    <xsl:choose>
      <xsl:when test = "override[@integrator=$Integrator and @supported='TRUE'] and @value">
        <td align="center" bgcolor="lightgreen">2.1</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="override[@integrator=$Integrator]" mode="value"/>
           (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td align="center"><xsl:apply-templates select="override[@integrator=$Integrator]" mode="suggestedValue"/></td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and @supported='TRUE']">
        <td align="center" bgcolor="lightgreen">2.1</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="default" mode="value"/>
           (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td align="center"><xsl:apply-templates select="override[@integrator=$Integrator]" mode="suggestedValue"/></td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and @supported='FALSE' and @value]">
        <td align="center" bgcolor="#FF3366">-</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="override[@integrator=$Integrator]" mode="value"/>
          (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td></td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and @supported='FALSE']">
        <td align="center" bgcolor="#FF3366">-</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="default" mode="value"/>
          (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td></td>
      </xsl:when>
      <xsl:when test = "override[@integrator=$Integrator and not(@supported)]">
        <td align="center" bgcolor="gray">...</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center" bgcolor="gray"><xsl:value-of select="override"/></td>
      </xsl:when>
      <xsl:when test = "default[@supported='TRUE']">
        <td align="center" bgcolor="green">2.1</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="default" mode="value"/>
          (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td align="center"><xsl:apply-templates select="default" mode="suggestedValue"/></td>
      </xsl:when>
      <xsl:when test = "default[@supported='FALSE']">
        <td align="center" bgcolor="red">-</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td align="center">
          <xsl:apply-templates select="default" mode="value"/>
          (<xsl:apply-templates select="default[@persistent='TRUE']" mode="persistent"/>
          <xsl:apply-templates select="default[@persistent='FALSE']" mode="volatile"/>)
        </td>
        <td></td>
      </xsl:when>
      <xsl:otherwise>
        <td align="center" bgcolor="yellow">??</td>
        <td><xsl:call-template name="Notes_disp" /></td>
        <td></td><td></td>
      </xsl:otherwise>
    </xsl:choose> 
  </xsl:template>

   <xsl:template match="override" mode="name">
    <xsl:value-of select="@name"/>
  </xsl:template>
  <xsl:template match="override" mode="value">
    <xsl:value-of select="@value"/>
  </xsl:template>
  <xsl:template match="override" mode="suggestedValue">
    <xsl:value-of select="@suggestedValue"/>
  </xsl:template>
  <xsl:template match="default" mode="value">
    <xsl:value-of select="@value"/>
  </xsl:template>
  <xsl:template match="default" mode="suggestedValue">
    <xsl:value-of select="@suggestedValue"/>
  </xsl:template>
  <xsl:template match="default" mode="persistent">Persistent</xsl:template>
  <xsl:template match="default" mode="volatile">Volatile</xsl:template>


  <xsl:template name="Notes_disp">
    <ul>
    <xsl:choose>
      <xsl:when test = "default[@changeApplies='']">
      </xsl:when>
      <xsl:when test = " default[@changeApplies='onReboot' or @changeApplies='OnReboot']">
        <li style="font-weight: bold; color: Orange">
          To take effect, changes to this parameter require a REBOOT
        </li>
      </xsl:when>
      <xsl:when test = " default[@changeApplies='onEnable' or @changeApplies='OnEnable']">
        <li style="font-weight: bold; color: Orange">
          To take effect, changes to this parameter requires the adminState to be DISABLED
        </li>
      </xsl:when>
      <xsl:otherwise>
        <li style="font-weight: bold; color: Red">
          ERROR: value of "changeApplies" is unknown
        </li>
      </xsl:otherwise>
    </xsl:choose>
    <xsl:choose>
      <xsl:when test=" $Integrator!='RADISYS'">
        <xsl:for-each select="Notes[@from=$Integrator or not(@from)]">
          <li style="font-weight: bold; color: Maroon">
            <xsl:value-of disable-output-escaping="yes" select="text()" />
          </li>
        </xsl:for-each>
      </xsl:when>
      <xsl:when test="$Integrator='RADISYS'">
        <xsl:for-each select="Notes[@from='RADISYS' or @from='AIR' or @from='RSYS' or @form or not(@from)]">
          <li style="font-weight: bold; color: Blue">
            <xsl:value-of disable-output-escaping="yes" select="text()" />
          </li>
        </xsl:for-each>
      </xsl:when>
      <xsl:otherwise> <!-- NOTHING --> </xsl:otherwise>
    </xsl:choose>
    <xsl:choose>
      <xsl:when test="mibGroup!='' ">
        <li>
          <font size="0.5">GROUP: <xsl:value-of select="mibGroup" /></font>
        </li>
      </xsl:when>
      <xsl:otherwise></xsl:otherwise>
    </xsl:choose>
    <xsl:choose>
      <xsl:when test="MIB_id!='' and MIB_id!='PARAM_ID_INVALID'">
        <li>
          <font size="0.5">MIB: <xsl:value-of select="MIB_id" /></font>
        </li>
      </xsl:when>
      <xsl:otherwise></xsl:otherwise>
    </xsl:choose>
  </ul>
</xsl:template>
  
  <xsl:template name="Write">
      <xsl:choose>
        <xsl:when test="RADISYS/override[@integrator=$Integrator and @access='readWrite']">
          <td align="center" style="font-weight: bold; color:Maroon">W</td>
        </xsl:when>
        <xsl:when test="RADISYS/override[@integrator=$Integrator and @access='readOnly']">
          <td align="center" style="font-weight: normal; color:Maroon">r</td>
        </xsl:when>
        <xsl:when test="RADISYS/default[@access='readWrite']">
          <td align="center" style="font-weight: bold; color:Blue">W</td>
        </xsl:when>
        <xsl:when test="RADISYS/default[@access='readOnly']">
          <td align="center" style="font-weight: normal; color:Blue">r</td>
        </xsl:when>
        <xsl:when test="@access='readWrite'">
          <td align="center" style="font-weight: bold; color:Black">W</td>
        </xsl:when>
        <xsl:when test="@access='readOnly'">
          <td align="center" style="font-weight: normal; color:Black">r</td>
        </xsl:when>
        <xsl:otherwise>
          <td bgcolor="gray" align="center" style="font-weight: bold; color:Black">???</td>
        </xsl:otherwise>
      </xsl:choose>
  </xsl:template>

  <xsl:template name="Notification">
    <td><ul>
      <xsl:choose>
        <xsl:when test="RADISYS/default[@supported='TRUE'] and @activeNotify='forceDefaultEnabled' and @forcedInform='true'">
          <li style="font-weight: bold; color:Black">Default Active Notification</li>
          <li style="font-weight: bold; color:Black">Forced Inform</li>
        </xsl:when>
        <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE'] and @activeNotify='forceDefaultEnabled' and @forcedInform='true'">
          <li style="font-weight: bold; color:Black">Default Active Notification</li>
          <li style="font-weight: bold; color:Black">Forced Inform</li>
        </xsl:when>
        <xsl:when test="RADISYS/default[@supported='TRUE'] and @activeNotify='forceDefaultEnabled'">
          <li style="font-weight: bold; color:Black">Default Active Notification</li>
        </xsl:when>
        <xsl:when test="RADISYS/default[@supported='TRUE'] and @forcedInform='true'">
          <li style="font-weight: bold; color:Black">Forced Inform</li>
        </xsl:when>
        <xsl:when test="RADISYS/default[@supported='TRUE'] and @activeNotify='canDeny'">
          <li style="font-weight: bold; color:Black">Can Deny SPA</li>
        </xsl:when>
        <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE' and @notificationType='2']">
          <li style="font-weight: bold; color:Maroon">Set to Active Notification by default for <xsl:value-of select="$Integrator"/></li>
        </xsl:when>
        <xsl:when test="RADISYS/override[@integrator=$Integrator and @supported='TRUE' and @notificationType='1']">
          <li style="font-weight: bold; color:Maroon">Set to Passive Notification by default for <xsl:value-of select="$Integrator"/></li>
        </xsl:when>
        <xsl:when test="RADISYS/default[@supported='TRUE' and @notificationType='2']">
          <li style="font-weight: bold; color:Blue">May be set to Active Notification by HMS</li>
        </xsl:when>
        <xsl:when test="RADISYS/default[@supported='TRUE' and @notificationType='1']">
          <li style="font-weight: bold; color:Blue">May be set to Passive Notification by HMS</li>
        </xsl:when> 
        <xsl:when test="RADISYS/default[@supported='FALSE']">
          <!-- <li style="font-weight: bold; color:Black"></li> -->
        </xsl:when>
        <xsl:when test="not(@activeNotify)"></xsl:when>
        <xsl:otherwise><li bgcolor="gray">??</li></xsl:otherwise>
      </xsl:choose>
    </ul></td>
  </xsl:template>
  
</xsl:stylesheet>
